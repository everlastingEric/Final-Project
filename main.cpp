#include <unordered_map>
#include <stack>
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

struct range {
    int lBound;
    int rBound;
    range (int l, int r) {
        lBound = l;
        rBound = r;
    }
};



class BST {
    public:
        BST(int capacity, int root) {
            tree = new node[capacity];
	        tree[0] = node(root);
            leafs.insert({0, range(-2147483648, 2147483647)});
	        size = 1;
        }

        ~BST() {
            delete[] tree;
        }

        void insert(int n) {
            tree[size] = node(n);
            for (auto itr = leafs.begin(); itr != leafs.end(); itr++) {
                if (n < tree[itr->first].val && n > itr->second.lBound) {
                    tree[itr->first].left = size;
                    leafs.insert({size, range(itr->second.lBound, tree[itr->first].val)});
                    itr->second.lBound = tree[itr->first].val;
                    if (itr->second.lBound == itr->second.rBound) {
                        leafs.erase(itr);
                    }
                    break;
                }
                else if (n > tree[itr->first].val && n < itr->second.rBound) {
                    tree[itr->first].right = size;
                    leafs.insert({size, range(tree[itr->first].val, itr->second.rBound)});
                    itr->second.rBound = tree[itr->first].val;
                    if (itr->second.lBound == itr->second.rBound) {
                        leafs.erase(itr);
                    }
                    break;
                }
            }
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
        unordered_map<int, range> leafs;
	    int root;
	    int size;
	    int capacity;
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

