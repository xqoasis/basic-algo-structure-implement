// a -> val = "123"
// map[123] = list{a}
// (dfs)node if node->val in the map, insert node-> name(filename) to map[node->val]
// map[123] = lista, map[234] = listb, 
#include <unordered_map>
#include <iostream>
using namespace std;
// struct: node->name = filename, node->val = content, node -> child = {Node*}
int main() {
    //root
    unordered_map<string, vector<string>> map;
    helper(root, map);
    for (auto ite: map) {
        if(ite.second.size() >1) {
            // at least two files
            // cout

        }
    }
}

void helper(Node* root, map) {
    if (root == nullptr) return;
    // search trie-> leaf node of trie ->find the list
    list.insert(node->name);
    // if didn't find a leaf, add the root -> val to the trie (global)

    // map[root -> val].insert(node->name); //
    for (auto c: root -> child) {
        helper(c);
    }
}
// 1. compact the content
//    "abcd" "dcba"
// a -> list[e, d, f] -> size 8 -> tree

// map[1] -> map[] -> 

// 1. avoid hash collision, 2. save mem
// 

// 2. trie -> check whether two files have the same content

"1": "abcd", "2":"abc"
 abc - list["2"]
 d - list["1"]

