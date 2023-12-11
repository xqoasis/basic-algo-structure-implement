#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

class Trie{
private:
  // value is its index
  bool isWord = false;
  Trie * children[26] = {};


public:
// insert
// search
  void insert(string word){
    Trie * cnt = this;
    for (char c : word){
      int n = c - 'a';//int
      if (cnt -> children[n] == nullptr){
        cnt -> children[n] = new Trie;
      }

      cnt = cnt->children[n];
    }
    cnt -> isWord = true;
  }

  bool search(string word){
    Trie * cnt = this;
    for (char c : word){
      int n = c - 'a';
      if (cnt -> children[n] == nullptr){
        return false;
      }
      cnt = cnt -> children[n];
    }

    if (cnt -> isWord == false){
      return false;
    }

    return true;

  }

  int search_prefix(string word){
    
    Trie * cnt = this;
    for (char c : word){
      int n = c - 'a';
      if (cnt -> children[n] == nullptr){
        return 0;
      }
      cnt = cnt -> children[n];
    }

    return search_all(cnt);
  }

  int search_all(Trie* root){
    int f = 0;
    if (root == nullptr){
      return 0;
    }

    if (root->isWord == 1){
      f ++;
    }


    for (int i = 0; i < 26; ++i){
      f += search_all(root->children[i]);
    }

    return f;

  }



};

// To execute C++, please define "int main()"
int main() {
  Trie trie;
  vector<string> words = { "apk", "app", "apple","arp", "array" };
  for (auto w : words){
    trie.insert(w);
  }
  int res = trie.search_prefix("5");
  cout << res <<endl;
  return 0;
}
