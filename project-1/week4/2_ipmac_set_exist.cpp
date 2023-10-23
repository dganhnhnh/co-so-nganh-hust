#include <bits/stdc++.h>
using namespace std;


class BST
{
    int data;
    BST *left, *right;

public:
    BST();
    BST(int);
    BST *Insert(BST *, int);
    void Inorder(BST *);
};

BST::BST()
    : data(0), left(NULL), right(NULL)
{
}

// Parameterized Constructor definition.
BST::BST(int value)
{
    data = value;
    left = right = NULL;
}

// Insert function definition.
BST *BST::Insert(BST *root, int value)
{
    if (!root)
    {

        // Insert the first node, if root is NULL.
        return new BST(value);
    }
    // Insert data.
    if (value > root->data)
    {
        root->right = Insert(root->right, value);
    }
    else if (value < root->data)
    {
        root->left = Insert(root->left, value);
    }
    return root;
}
// ## sort
void BST::Inorder(BST *root)
{
    if (!root)
    {
        return;
    }
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

// Driver code
int main()
{
    int n; cin>>n;
    BST b, *root = NULL;
    root = b.Insert(root, 50);
    int a1,a2;
    cout << 0;
    cin>>a1;
    b.Insert(root,a1);
    for (int i = 1; i < n; i++)
    {
        cin >> a2;
        b.Insert(root, a2);
        // search here
 
        a1=a2;
    }
    b.Inorder(root);
    return 0;
}
