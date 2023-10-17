#include <bits/stdc++.h> 
using namespace std;

struct Node {
    int id;
    vector<Node*> children;

    Node(int _id) : id(_id) {}
};

map<int, Node*> nodes;
Node* root = nullptr;

void PreOrder(Node* node) {
    if (node == nullptr) return;
    cout << node->id << " ";
    for (Node* child : node->children) {
        PreOrder(child);
    }
}

void InOrder(Node* node) {
    if (node == nullptr) return;
    if (node->children.size() >= 1) {
        InOrder(node->children[0]);
    }
    cout << node->id << " ";
    for (int i = 1; i < node->children.size(); i++) {
        InOrder(node->children[i]);
    }
}

void PostOrder(Node* node) {
    if (node == nullptr) return;
    for (Node* child : node->children) {
        PostOrder(child);
    }
    cout << node->id << " ";
}

int main() {
    string command;
    while (getline(cin, command)) {  
        stringstream ss(command);  
        string action;
        ss >> action;

        if (action == "MakeRoot") {
            int u;
            ss >> u;
            nodes[u] = new Node(u);
            root = nodes[u];
        } else if (action == "Insert") {
            int u, v;
            ss >> u >> v;
            if (nodes.find(u) == nodes.end() && !(nodes.find(v) == nodes.end())) {
                nodes[u] = new Node(u);
                nodes[v]->children.push_back(nodes[u]);
            }
        } else if (action == "PreOrder") {
            PreOrder(root);
            cout << endl;
        } else if (action == "InOrder") {
            InOrder(root);
            cout << endl;
        } else if (action == "PostOrder") {
            PostOrder(root);
            cout << endl;
        } else if (action == "*") {
            break;
        }
    }
    return 0;
}