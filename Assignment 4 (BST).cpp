#include <iostream>
using namespace std;

struct node {
    int data;
    node *L;
    node *R;
};

node *root, *temp;
int key;

class bst {
public:
    bst() {
        root = NULL;
    }

    void create();
    void insert(node*, node*);
    void disin(node*);
    void dispre(node*);
    void dispost(node*);
    void search(node*, int);
    int height(node*);
    void mirror(node*);
    void min(node*);
};

void bst::create() {
    char ans;
    do {
        temp = new node;
        cout << "\nEnter the data: ";
        cin >> temp->data;
        temp->L = NULL;
        temp->R = NULL;

        if (root == NULL)
            root = temp;
        else
            insert(root, temp);

        cout << "Do you want to insert more values? (y/n): ";
        cin >> ans;
    } while (ans == 'y');
}

void bst::insert(node *root, node *temp) {
    if (temp->data > root->data) {
        if (root->R == NULL)
            root->R = temp;
        else
            insert(root->R, temp);
    } else {
        if (root->L == NULL)
            root->L = temp;
        else
            insert(root->L, temp);
    }
}

void bst::disin(node *root) {
    if (root != NULL) {
        disin(root->L);
        cout << root->data << " ";
        disin(root->R);
    }
}

void bst::dispre(node *root) {
    if (root != NULL) {
        cout << root->data << " ";
        dispre(root->L);
        dispre(root->R);
    }
}

void bst::dispost(node *root) {
    if (root != NULL) {
        dispost(root->L);
        dispost(root->R);
        cout << root->data << " ";
    }
}

void bst::search(node *root, int key) {
    cout << "\nEnter the key to search: ";
    cin >> key;

    temp = root;
    while (temp != NULL) {
        if (key == temp->data) {
            cout << "Key FOUND!" << endl;
            return;
        }
        if (key > temp->data)
            temp = temp->R;
        else
            temp = temp->L;
    }
    cout << "Key NOT FOUND." << endl;
}

int bst::height(node *root) {
    if (root == NULL)
        return 0;

    int hl = height(root->L);
    int hr = height(root->R);

    return max(hl, hr) + 1;
}

void bst::min(node *root) {
    temp = root;
    while (temp->L != NULL)
        temp = temp->L;
    cout << "Minimum element: " << temp->data << endl;
}

void bst::mirror(node *root) {
    if (root != NULL) {
        mirror(root->L);
        mirror(root->R);

        temp = root->L;
        root->L = root->R;
        root->R = temp;
    }
}

int main() {
    bst t;
    int ch;
    char ans;

    do {
        cout << "\n==================== MENU ====================";
        cout << "\n1. Insert node";
        cout << "\n2. Number of nodes in longest path";
        cout << "\n3. Find minimum element";
        cout << "\n4. Mirror the tree (and display inorder)";
        cout << "\n5. Search for a key";
        cout << "\n6. Inorder Traversal";
        cout << "\n7. Preorder Traversal";
        cout << "\n8. Postorder Traversal";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                t.create();
                break;
            case 2:
                cout << "\nHeight (Longest Path Length): " << t.height(root) << endl;
                break;
            case 3:
                t.min(root);
                break;
            case 4:
                t.mirror(root);
                cout << "Mirror tree inorder traversal: ";
                t.disin(root);
                cout << endl;
                break;
            case 5:
                t.search(root, key);
                break;
            case 6:
                cout << "\nInorder Traversal: ";
                t.disin(root);
                cout << endl;
                break;
            case 7:
                cout << "\nPreorder Traversal: ";
                t.dispre(root);
                cout << endl;
                break;
            case 8:
                cout << "\nPostorder Traversal: ";
                t.dispost(root);
                cout << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
