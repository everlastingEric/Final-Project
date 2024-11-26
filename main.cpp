#include <vector>
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
};

class BST {
    public:
        void insert(int n) {
            tree.push_back(node(n));
            if (tree.size() == 1) {
                return;
            }
            int idx = 0;
            while (true) {
                if (n > tree[idx].val) {
                    if (tree[idx].right == -1) {
                        tree[idx].right = tree.size() - 1;
                        return;
                    }
                    idx = tree[idx].right;
                }
                else {
                    if (tree[idx].left == -1) {
                        tree[idx].left = tree.size() - 1;
                        return;
                    }
                    idx = tree[idx].left;
                }
            }
        }

        void preorder() {
            if (tree.size() == 0) return;
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

        int size() {
            return tree.size();
        }
    private:
        vector<node> tree;
};

int main() {
    BST t;

    int size;
    cin >> size;

    for (int i = 0; i < size; i++) {
        int n;
        cin >> n;
        t.insert(n);
    }

    cout << t.size() << endl;
    t.preorder();
}

