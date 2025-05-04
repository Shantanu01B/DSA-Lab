#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct node {
    string vertex;
    int time;
    node *next;
};

class adjmatlist {
    int m[10][10], n;
    string v[20];
    node *head[20];
    node *temp;

public:
    adjmatlist() {
        for (int i = 0; i < 20; i++)
            head[i] = NULL;
        temp = NULL;
    }

    void getgraph();
    void adjlist();
    void displaym();
    void displaya();
};

void adjmatlist::getgraph() {
    char ch;
    cout << "\nEnter number of cities (max 20): ";
    cin >> n;

    cout << "Enter names of the cities:\n";
    for (int i = 0; i < n; i++)
        cin >> v[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\nIs there a path from " << v[i] << " to " << v[j] << "? (y/n): ";
            cin >> ch;

            if (ch == 'y') {
                cout << "Enter time required (in minutes): ";
                cin >> m[i][j];
            } else if (ch == 'n') {
                m[i][j] = 0;
            } else {
                cout << "Invalid input. Assuming no path.\n";
                m[i][j] = 0;
            }
        }
    }

    adjlist();
}

void adjmatlist::adjlist() {
    for (int i = 0; i < n; i++) {
        node *p = new node;
        p->vertex = v[i];
        p->time = 0;
        p->next = NULL;
        head[i] = p;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                node *p = new node;
                p->vertex = v[j];
                p->time = m[i][j];
                p->next = NULL;

                temp = head[i];
                while (temp->next != NULL)
                    temp = temp->next;

                temp->next = p;
            }
        }
    }
}

void adjmatlist::displaym() {
    cout << "\nAdjacency Matrix:\n\t";
    for (int j = 0; j < n; j++)
        cout << v[j] << "\t";
    
    for (int i = 0; i < n; i++) {
        cout << "\n" << v[i] << "\t";
        for (int j = 0; j < n; j++)
            cout << m[i][j] << "\t";
    }
    cout << endl;
}

void adjmatlist::displaya() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\nNo adjacency list present.\n";
            break;
        }

        cout << head[i]->vertex;
        temp = head[i]->next;

        while (temp != NULL) {
            cout << " -> " << temp->vertex;
            temp = temp->next;
        }
        cout << endl;
    }

    cout << "\nPaths and Time Required:\n";
    for (int i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\nNo adjacency list present.\n";
            break;
        }

        temp = head[i]->next;
        while (temp != NULL) {
            cout << head[i]->vertex << " -> " << temp->vertex 
                 << " [Time required: " << temp->time << " min]\n";
            temp = temp->next;
        }
    }
}

int main() {
    adjmatlist a;
    int choice;

    while (true) {
        cout << "\n\nMENU";
        cout << "\n1. Enter Graph";
        cout << "\n2. Display Adjacency Matrix";
        cout << "\n3. Display Adjacency List";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: a.getgraph(); break;
            case 2: a.displaym(); break;
            case 3: a.displaya(); break;
            case 4: exit(0);
            default: cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
