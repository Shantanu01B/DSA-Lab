# Consider telephone book database of N clients. Make use of a hash table implementation
# to quickly look up client‘s telephone number. Make use of two collision handling
# techniques and compare them using number of comparisons required to find a set of
# telephone numbers

def tele_database():
    phone_data = []
    n = int(input("Enter Number of Clients: "))
    print("Enter phone Numbers: \n")
    for i in range(n):
        while True:
            try:
                x = int(input("--->"))
                phone_data.append(x)
                break
            except ValueError:
                print("Invalid input. Please enter a valid phone number.")
    return phone_data

def hash_function_1(key_ele, m_size):
    
    h1 = key_ele % m_size
    return h1

def hash_function_2(key_ele):
  
    h2 = 1 + (key_ele % 11)
    return h2

def get_valid_input(prompt, valid_options):
    while True:
        try:
            user_input = int(input(prompt))
            if user_input in valid_options:
                return user_input
            else:
                print(f"Invalid choice. Please enter one of the following: {valid_options}")
        except ValueError:
            print("Invalid input. Please enter a number.")

def hash_table():
    phone_database = tele_database()
    m = get_valid_input("Enter Hash Table Size: ", range(1, 101))  # Hash table size between 1 and 100
    hash_table = [-1] * m
    
    opt = get_valid_input("If collision occurs, which collision resolution technique do you want to use? \n\t1. Linear Probing \n\t2. Double Hashing: ", [1, 2])
    
    for k in phone_database:
        h_1 = hash_function_1(k, m)
        h_2 = hash_function_2(k)
        
        if hash_table[h_1] == -1:
            hash_table[h_1] = k
        else:
            if opt == 1:
                # Linear Probing
                while hash_table[h_1] != -1:
                    h_1 = (h_1 + 1) % m  # Move to the next slot
                hash_table[h_1] = k
            elif opt == 2:
                # Double Hashing
                i = 0
                while hash_table[h_1] != -1:
                    i += 1
                    h_1 = (h_1 + i * h_2) % m  
                hash_table[h_1] = k

    print("\nHash Table:")
    print("Index \t Key")
    for i in range(len(hash_table)):
        if hash_table[i] != -1:
            print(f"{i} \t {hash_table[i]}")
        else:
            print(f"{i} \t -1")


hash_table()

