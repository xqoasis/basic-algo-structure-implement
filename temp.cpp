#include <iostream>
class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(int newvalue);
    ~TreeNode();
};

TreeNode::TreeNode(int newvalue)
{
    val = newvalue;
    left = nullptr;
    right = nullptr;
}

TreeNode::~TreeNode()
{
    delete left, right;
}


class bst
{
private:
    TreeNode* root;
public:
    bst(TreeNode* root);
    ~bst();

    void Insert(int v) {
        TreeNode* newnode = new TreeNode(v);
        TreeNode* p = root;
        while (p != nullptr)
        {
            if (v < p -> val) {
                if (p -> left == nullptr){
                    p -> left = newnode;
                    break;
                }
                p = p -> left;
            }else if (v > p -> val) {
                if (p -> right == nullptr) {
                    p -> right = newnode;
                    break;
                };
                p = p -> right;
            }else {
                return;
            }
        }
    };
    void Delete(int v){
        delHelper(root, v);
    };
    TreeNode* delHelper(TreeNode* cntroot, int v){
        if (cntroot == nullptr) return nullptr;
        if (cntroot -> val == v) {
            if (cntroot -> left == nullptr) return cntroot -> right;
            if (cntroot -> right == nullptr) return cntroot -> left;
            // has both son
            TreeNode* rMin = findRmin(cntroot -> right);
            int rMinval = rMin -> val;
            cntroot -> right = delHelper(cntroot -> right, rMinval);

            rMin -> left = cntroot -> left;
            rMin -> right = cntroot -> right;
            cntroot = rMin;
            return cntroot;
        }else {
            if (v < cntroot -> val) {
                cntroot -> left = delHelper(cntroot -> left, v);
            }else {
                cntroot -> right = delHelper(cntroot -> right, v);
            }
        }
        return cntroot;

    }

    TreeNode* findRmin(TreeNode* root) {
        while (root -> left != nullptr) {
            root = root -> left;
        }
        return root;
    }
};

bst::bst(TreeNode* root)
{
    root = root;
}

bst::~bst()
{
    delete root;
}


int main(){
    return 0;
}