#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct node {
    char name[20];
    node *next;
    node *down;
    int flag;
};

class Gll {
    char ch[20];
    int n, i;
    node *head = NULL, *temp = NULL, *t1 = NULL, *t2 = NULL;

public:
    node* create();
    void insertb();
    void insertc();
    void inserts();
    void insertss();
    void displayb();
};

node* Gll::create() {
    node *p = new node;
    p->next = NULL;
    p->down = NULL;
    p->flag = 0;
    cout << "Enter name: ";
    cin >> p->name;
    return p;
}

void Gll::insertb() {
    if (head == NULL) {
        cout << "\nCreating Book...\n";
        t1 = create();
        head = t1;
    } else {
        cout << "\nBook already exists!\n";
    }
}

void Gll::insertc() {
    if (head == NULL) {
        cout << "\nNo book found. Please insert a book first.\n";
    } else {
        cout << "\nHow many chapters you want to insert? ";
        cin >> n;
        for (i = 0; i < n; i++) {
            cout << "\nCreating Chapter " << (i + 1) << "...\n";
            t1 = create();
            if (head->flag == 0) {
                head->down = t1;
                head->flag = 1;
            } else {
                temp = head->down;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = t1;
            }
        }
    }
}

void Gll::inserts() {
    if (head == NULL) {
        cout << "\nNo book found.\n";
    } else {
        cout << "\nEnter the chapter name to insert sections into: ";
        cin >> ch;

        if (head->flag == 0) {
            cout << "\nNo chapters found in the book.\n";
        } else {
            temp = head->down;
            while (temp != NULL) {
                if (!strcmp(ch, temp->name)) {
                    cout << "\nHow many sections you want to insert in '" << ch << "'? ";
                    cin >> n;
                    for (i = 0; i < n; i++) {
                        cout << "\nCreating Section " << (i + 1) << "...\n";
                        t1 = create();
                        if (temp->flag == 0) {
                            temp->down = t1;
                            temp->flag = 1;
                            t2 = temp->down;
                        } else {
                            t2 = temp->down;
                            while (t2->next != NULL)
                                t2 = t2->next;
                            t2->next = t1;
                        }
                    }
                    return;
                }
                temp = temp->next;
            }
            cout << "\nChapter not found!\n";
        }
    }
}

void Gll::insertss() {
    if (head == NULL) {
        cout << "\nNo book found.\n";
    } else {
        cout << "\nEnter the chapter name containing the section: ";
        cin >> ch;
        if (head->flag == 0) {
            cout << "\nNo chapters found in the book.\n";
        } else {
            temp = head->down;
            while (temp != NULL) {
                if (!strcmp(ch, temp->name)) {
                    char sectionName[20];
                    cout << "\nEnter the section name to insert subsections into: ";
                    cin >> sectionName;

                    if (temp->flag == 0) {
                        cout << "\nNo sections found in the chapter.\n";
                        return;
                    } else {
                        t1 = temp->down;
                        while (t1 != NULL) {
                            if (!strcmp(sectionName, t1->name)) {
                                cout << "\nHow many subsections you want to insert in '" << sectionName << "'? ";
                                cin >> n;
                                for (i = 0; i < n; i++) {
                                    cout << "\nCreating Subsection " << (i + 1) << "...\n";
                                    t2 = create();
                                    if (t1->flag == 0) {
                                        t1->down = t2;
                                        t1->flag = 1;
                                    } else {
                                        node* tempSub = t1->down;
                                        while (tempSub->next != NULL)
                                            tempSub = tempSub->next;
                                        tempSub->next = t2;
                                    }
                                }
                                return;
                            }
                            t1 = t1->next;
                        }
                        cout << "\nSection not found!\n";
                    }
                }
                temp = temp->next;
            }
            cout << "\nChapter not found!\n";
        }
    }
}

void Gll::displayb() {
    if (head == NULL) {
        cout << "\nNo book found!\n";
    } else {
        temp = head;
        cout << "\n\n=== BOOK STRUCTURE ===\n";
        cout << "\nBOOK: " << temp->name << "\n";

        if (temp->flag == 1) {
            temp = temp->down;
            while (temp != NULL) {
                cout << "\n  CHAPTER: " << temp->name;
                t1 = temp;
                if (t1->flag == 1) {
                    t1 = t1->down;
                    while (t1 != NULL) {
                        cout << "\n    SECTION: " << t1->name;
                        t2 = t1;
                        if (t2->flag == 1) {
                            t2 = t2->down;
                            while (t2 != NULL) {
                                cout << "\n      SUBSECTION: " << t2->name;
                                t2 = t2->next;
                            }
                        }
                        t1 = t1->next;
                    }
                }
                temp = temp->next;
            }
        }
        cout << "\n=======================\n";
    }
}

int main() {
    Gll g;
    int x;
    while (1) {
        cout << "\n\n====== MENU ======";
        cout << "\n1. Insert Book";
        cout << "\n2. Insert Chapter";
        cout << "\n3. Insert Section";
        cout << "\n4. Insert Subsection";
        cout << "\n5. Display Book Structure";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> x;

        switch (x) {
            case 1: g.insertb(); break;
            case 2: g.insertc(); break;
            case 3: g.inserts(); break;
            case 4: g.insertss(); break;
            case 5: g.displayb(); break;
            case 6: exit(0);
            default: cout << "\nInvalid choice. Try again!\n";
        }
    }
    return 0;
}
