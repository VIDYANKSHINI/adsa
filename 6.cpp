
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    int lbit, rbit;
};

class TBT {
    Node *root;

public:
    TBT() {
        root = NULL;
    }

    void insert(int x) {
        Node *temp = new Node;
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        temp->lbit = 0;
        temp->rbit = 0;

        if (root == NULL) {
            root = temp;
            return;
        }

        Node *p = root;
        Node *parent = NULL;

        while (p != NULL) {
            parent = p;

            if (x < p->data) {
                if (p->lbit == 1)
                    p = p->left;
                else
                    break;
            }
            else {
                if (p->rbit == 1)
                    p = p->right;
                else
                    break;
            }
        }

        if (x < parent->data) {
            temp->left = parent->left;
            temp->right = parent;
            parent->left = temp;
            parent->lbit = 1;
        }
        else {
            temp->right = parent->right;
            temp->left = parent;
            parent->right = temp;
            parent->rbit = 1;
        }
    }

    void inorder() {
        Node *p = root;

        while (p != NULL && p->lbit == 1)
            p = p->left;

        while (p != NULL) {
            cout << p->data << " ";

            if (p->rbit == 0)
                p = p->right;
            else {
                p = p->right;

                while (p != NULL && p->lbit == 1)
                    p = p->left;
            }
        }
    }

    void preorder() {
        Node *p = root;

        while (p != NULL) {
            cout << p->data << " ";

            if (p->lbit == 1)
                p = p->left;
            else if (p->rbit == 1)
                p = p->right;
            else {
                while (p != NULL && p->rbit == 0)
                    p = p->right;

                if (p != NULL)
                    p = p->right;
            }
        }
    }
};

int main() {
    TBT t;
    int n, x;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter values: ";

    for (int i = 0; i < n; i++) {
        cin >> x;
        t.insert(x);
    }

    cout << "\nInorder Traversal: ";
    t.inorder();

    cout << "\nPreorder Traversal: ";
    t.preorder();

    return 0;
}
