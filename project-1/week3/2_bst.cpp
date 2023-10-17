#include <bits/stdc++.h> 
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(NULL), right(NULL) {}
};

Node* insert(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

void preOrderTraversal(Node* root) {
    if (root == NULL) return;
    cout << root->key << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main() {
    Node* root = NULL;
    string line;

    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }

        stringstream ss(line);
        string command;
        int key;
        ss >> command >> key;

        if (command == "insert") {
            root = insert(root, key);
        }
    }

    preOrderTraversal(root);
    cout << endl;

    return 0;
}