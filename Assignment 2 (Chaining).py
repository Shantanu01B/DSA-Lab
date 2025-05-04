# Group A:2
# Implement all the functions of a dictionary (ADT) using hashing and handle collisions using
# chaining #with / without replacement. Data: Set of (key, value) pairs, Keys are mapped to
# values, Keys must be comparable, a)Keys must be unique. Standard Operations: Insert(key,
# value), Find(key), Delete(key)


table = []
b, totl = 0, 0
bucket = {}

def create():
    global b
    b = int(input("Enter the table size: "))
    for i in range(b):
        table.append([None, -1])
        bucket[i] = -1

def print_table():
    global b
    print("\nHash Table State:")
    for i in range(b):
        print(f"Index {i}: Key = {table[i][0]}, Link = {table[i][1]}")
    print()

def chain_insert(key):
    global b, totl
    h = key % b

    if table[h][0] is None:
        table[h][0] = key
        bucket[h] = h
    else:
        flag = 0
        for i in range(b):
            new_h = (h + i) % b
            if table[new_h][0] is None:
                totl += 1
                flag = 1
                if bucket[h] != -1:
                    table[bucket[h]][1] = new_h
                bucket[h] = new_h
                table[new_h][0] = key
                break
        if flag == 0:
            print(f"Key {key} not inserted - table is full.")

def chain_search(key):
    global b
    h = key % b

    if table[h][0] == key:
        print(f"Key {key} is found at index {h}")
        return

    flag = 0
    chain = table[h][1]
    while chain != -1:
        if table[chain][0] == key:
            print(f"Key {key} is found at index {chain}")
            flag = 1
            break
        chain = table[chain][1]

    if flag == 0:
        print(f"Key {key} not found.")

def chain_delete(key):
    global b
    h = key % b

    if table[h][0] == key:
        table[h] = [None, -1]
        print(f"Key {key} was deleted from index {h}")
        return

    flag = 0
    prev_chain = h
    chain = table[h][1]

    while chain != -1:
        if table[chain][0] == key:
            table[prev_chain][1] = table[chain][1]
            table[chain] = [None, -1]
            print(f"Key {key} was deleted from index {chain}")
            flag = 1
            break
        prev_chain = chain
        chain = table[chain][1]

    if flag == 0:
        print(f"Key {key} not found.")

# Main Execution
create()

while True:
    ch = int(input("Enter 1-Table Menu | 0-EXIT: "))
    if ch == 1:
        while True:
            ch2 = int(input("Enter 1-Insert | 2-Search | 3-Delete | 0-BACK: "))
            if ch2 == 1:
                key = int(input("Enter the key to be inserted: "))
                chain_insert(key)
                print_table()
            elif ch2 == 2:
                key = int(input("Enter the key to be searched: "))
                chain_search(key)
                print_table()
            elif ch2 == 3:
                key = int(input("Enter the key to be deleted: "))
                chain_delete(key)
                print_table()
            elif ch2 == 0:
                print("Going back to main menu.")
                break
            else:
                print("Invalid option. Try again.")
    elif ch == 0:
        print("Exiting...")
        break
    else:
        print("Invalid option. Try again.")
