#include <iostream>
#include <vector>

class Node {
public:
    bool isRed;
    int val;
    Node* left;
    Node* right;

    Node() : isRed(false), val(0), left(nullptr), right(nullptr) {}
    Node(int v) : isRed(true), val(v), left(nullptr), right(nullptr) {}
};

class RBtree {
protected:
    Node* root;
    std::vector<Node*> arr;

public:
    RBtree();
    ~RBtree();

    bool isRed(Node* node);
    void rotateRight(Node* &node);
    void rotateLeft(Node* &node);
    void swapColor(Node* &node);
    void destruct(Node* node);
    void buildTree();
    void insert(Node* &node, Node* &vnode);
    void display(Node* node);
};

class Set : public RBtree {
public:
    Set();
    bool contains(const int toFind);
    void Delete();
    void insert(const int element);
    void print();
    Node* searchNode(const int toFind, Node* node) ;
    Node* getRoot() { return root; }
};

RBtree::RBtree() : root(nullptr) {}

RBtree::~RBtree() {
    if (root != nullptr)
        destruct(root);

    for (auto& node : arr)
        delete node;
}

bool RBtree::isRed(Node* node) {
    return (node != nullptr) && node->isRed;
}

void RBtree::rotateRight(Node* &node) {
    Node* temp = node->left;
    temp->right = node;
    temp->isRed = node->isRed;
    node->isRed = true;
    node = temp;
}

void RBtree::rotateLeft(Node* &node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->isRed = node->isRed;
    node->isRed = true;
    node = temp;
}

void RBtree::swapColor(Node* &node) {
    node->isRed = true;
    if (node->left != nullptr)
        node->left->isRed = false;
    if (node->right != nullptr)
        node->right->isRed = false;
}

void RBtree::destruct(Node* node) {
    if (node != nullptr) {
        destruct(node->left);
        destruct(node->right);
        delete node;
    }
}

void RBtree::buildTree() {
    int temparr[10] = {1, 4, 5, 8, 11, 6, 19, 2, 20, 0};
    for (int i = 0; i < 10; i++) {
        arr.push_back(new Node(temparr[i]));
        insert(root, arr[i]);
    }
    display(root);
}

void RBtree::insert(Node* &node, Node* &vnode) {
    if (node == nullptr) {
        node = vnode;
    } else if (node->val > vnode->val) {
        insert(node->left, vnode);
    } else if (node->val < vnode->val) {
        insert(node->right, vnode);
    }

    if (isRed(node->right) && !isRed(node->left)) {
        rotateLeft(node);
    }

    if (isRed(node->left) && isRed(node->left->left)) {
        rotateRight(node);
    }

    if (isRed(node->left) && isRed(node->right)) {
        swapColor(node);
    }
}

void RBtree::display(Node* node) {
    if (node != nullptr) {
        display(node->left);
        std::cout << node->val << " ";
        display(node->right);
    }
}

Set::Set() : RBtree() {}

Node* Set::searchNode(const int toFind, Node* node) {
    if (node == nullptr || node->val == toFind)
        return node;

    if (toFind > node->val)
        return searchNode(toFind, node->right);
    else
        return searchNode(toFind, node->left);
}

bool Set::contains(const int toFind) {
    return searchNode(toFind, root) != nullptr;
}

void Set::insert(const int element) {
    if (!contains(element)) {
        arr.push_back(new Node(element));
        RBtree::insert(root, arr.back());
    }
}

void Set::print() {
    for (auto it = arr.begin(); it != arr.end(); it++)
        std::cout << (*it)->val << " ";
    std::cout << "\n";
}

int main() {
    Set obj;
    obj.insert(10);
    obj.insert(11);
    obj.insert(12);
    auto n = obj.searchNode(14, obj.getRoot() );
    if (n != nullptr)
        std::cout << n->val;
    else
        std::cout << "Null";

    return 0;
}
