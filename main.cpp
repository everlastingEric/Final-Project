#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

struct node {
    int val;
    int left;
    int right;
    node(int value) {
        val = value;
        left = -1;
        right = -1;
    }

    node() {}
};

struct AVLNode {
    int val;
    int left;
    int right;
    int parent;
    int height;
    int refIdx;

    AVLNode(int value, int reference) {
        val = value;
        refIdx = reference;
        left = -1;
        right = -1;
        parent = -1;
        height = 1;
    }
    
    AVLNode() {
    }
};

class AVL {
    public:
        AVL(int capacity, int root, int rootRef) {
            tree = new AVLNode[capacity];
            tree[0] = AVLNode(root, rootRef);
            size = 1;
            rootIdx = 0;
            this->capacity = capacity;
        }

        ~AVL() {
            delete[] tree;
        }

        void insert(int n, int refIdx) {
            tree[size] = AVLNode(n, refIdx);
            int idx = rootIdx;
            bool inserted = false;
            while (!inserted) {
                if (n > tree[idx].val) {
                    if (tree[idx].right == -1) {
                        tree[idx].right = size;
                        tree[size].parent = idx;
                        inserted = true;
                    }
                    else {
                        idx = tree[idx].right;
                    }
                }
                else {
                    if (tree[idx].left == -1) {
                        tree[idx].left = size;
                        tree[size].parent = idx;
                        inserted = true;
                    }
                    else {
                        idx = tree[idx].left;
                    }
                }
            }

            while (idx != -1) {
                int balance = getHeight(tree[idx].left) - getHeight(tree[idx].right);
                
                if(balance > 1 && n > tree[tree[idx].left].val) {
                    rotateLeft(tree[idx].left);
                    rotateRight(idx);
                }
                else if (balance < -1 && n < tree[tree[idx].right].val) {
                    rotateRight(tree[idx].right);
                    rotateLeft(idx);
                }
                else if (balance > 1 && n < tree[tree[idx].left].val) {
                    rotateRight(idx);
                }
                else if (balance < -1 && n > tree[tree[idx].right].val) {
                    rotateLeft(idx);
                }
                tree[idx].height = max(getHeight(tree[idx].left), getHeight(tree[idx].right)) + 1;
                idx = tree[idx].parent;
            }

            size++;
        }

        int upper(int n) {
            int i = rootIdx;
            int idx = -1;
            int val;

            while (i != -1) {
                if (tree[i].val > n && idx == -1) {
                    val = tree[i].val;
                    idx = tree[i].refIdx;
                }
                else if (tree[i].val > n && tree[i].val < val) {
                    val = tree[i].val;
                    idx = tree[i].refIdx;
                }
                if (n >= tree[i].val) {
                    i = tree[i].right;
                } 
                else {
                    i = tree[i].left;
                }
            }
            return idx;
        }

    private:
        AVLNode* tree;
	    int rootIdx;
	    int size;
	    int capacity;
        int getHeight(int idx) {
            if (idx <= -1 || idx >= size) return 0;
            return tree[idx].height;
        }

        void rotateRight(int idx) {
            int subParent = tree[idx].parent;
            int leftChild = tree[idx].left;
            int leftRightChild = tree[leftChild].right;

            if (subParent == -1) {
                rootIdx = leftChild;
            }
            else {
                tree[subParent].left = leftChild;
            }
            tree[leftChild].parent = subParent;

            tree[leftChild].right = idx;
            tree[idx].parent = leftChild;

            tree[idx].left = leftRightChild;
            if (leftRightChild != -1) {
                tree[leftRightChild].parent = idx;
            }

            tree[idx].height = max(getHeight(tree[idx].left), getHeight(tree[idx].right)) + 1;
            tree[leftChild].height = max(getHeight(tree[leftChild].left), getHeight(tree[leftChild].right)) + 1;
        }

        void rotateLeft(int idx) {
            int subParent = tree[idx].parent;
            int rightChild = tree[idx].right;
            int rightLeftChild = tree[rightChild].left;

            if (subParent == -1) {
                rootIdx = rightChild;
            }
            else {
                tree[subParent].right = rightChild;
            }
            tree[rightChild].parent = subParent;

            tree[rightChild].left = idx;
            tree[idx].parent = rightChild;

            tree[idx].right = rightLeftChild;
            if (rightLeftChild != -1) {
                tree[rightLeftChild].parent = idx;
            }

            tree[idx].height = max(getHeight(tree[idx].left), getHeight(tree[idx].right)) + 1;
            tree[rightChild].height = max(getHeight(tree[rightChild].left), getHeight(tree[rightChild].right)) + 1;
        }
};


class BST {
    public:
        BST(int capacity, int root) {
            tree = new node[capacity];
            tree[0] = node(root);
            biggestIdx = 0;
            helper = new AVL(capacity, root, 0);
            this->capacity = capacity;
            size = 1;
        }

        ~BST() {
            delete[] tree;
            delete helper;
        }

        void insert(int n) {
            tree[size] = node(n);
            int idx = helper->upper(n);
            if (idx == -1) {
                tree[biggestIdx].right = size;
                biggestIdx = size;
            }
            else {
                bool inserted = false;
                while (!inserted) {
                    if (n > tree[idx].val) {
                        if (tree[idx].right == -1) {
                            tree[idx].right = size;
                            inserted = true;
                        }
                        idx = tree[idx].right;
                    }
                    else {
                        if (tree[idx].left == -1) {
                            tree[idx].left = size;
                            inserted = true;
                        }
                        idx = tree[idx].left;
                    }
                }
            }
            helper->insert(n, size);
            size++;
        }

        void preorder() {
            if (size == 0) return;
            stack<int> nodes;
            nodes.push(0);
            while (!nodes.empty()) {
                int curr = nodes.top();
                nodes.pop();
                cout << tree[curr].val << " ";
                if (tree[curr].right != -1) {
                    nodes.push(tree[curr].right);
                }
                if (tree[curr].left != -1) {
                    nodes.push(tree[curr].left);
                }
            }
            cout << endl;
        }

    private:
        node* tree;
        AVL* helper;
	    int root;
	    int size;
	    int capacity;
        int biggestIdx;
};

int main() {
    int size;
    cin >> size;
    int root;
    cin >> root;

    BST t(size, root);

    for (int i = 0; i < size - 1; i++) {
        int n;
        cin >> n;
        t.insert(n);
    }
    t.preorder();
}

