#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;    
    Node(int item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

// Note that it is not a generic inorder
// successor function. It mainly works
// when right child is not empty which is
// the case wwe need in BST delete
Node* getSuccessor(Node* curr){
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

// This function deletes a given key x from
// the give BST and returns modified root of
// the BST (if it is modified)
Node* delNode(Node* root, int x){

    // Base case
    if (root == nullptr) {
        cout << "\nNode " << x << " not found.\n";
        return root;
    }

    // If key to be searched is in a subtree
    if (root->key > x)
        root->left = delNode(root->left, x);
    else if (root->key < x)
        root->right = delNode(root->right, x);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // When both children are present
        Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}

// A utility function to insert a new node with 
// the given key
Node* insert(Node* node, int key) {
  
    // If the tree is empty, return a new node
    if (node == NULL) 
        return new Node(key);    
    
    // If the key is already present in the tree,
    // return the node
    if (node->key == key) 
        return node;
    
    // Otherwise, recur down the tree/ If the key
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (node->key < key) 
        node->right = insert(node->right, key);
    
    // If the key to be inserted is smaller than 
    // the node's key,insert it in the left subtree
    else 
        node->left = insert(node->left, key);
    
    // Return the (unchanged) node pointer
    return node;
}

// A utility function to do inorder tree traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Driver program to test the above functions
int main() {
    // Creating the following BST
    //      50
    //     /  \
    //    30   70
    //   / \   / \
    //  20 40 60 80

    Node* root = new Node(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 55);


    // Print inorder traversal of the BST
    inorder(root);
    cout << "\n";
    int x = 55;
    root = delNode(root, x);
    root = delNode(root, 88);

    inorder(root);
    cout << "\n";

    return 0;
}
