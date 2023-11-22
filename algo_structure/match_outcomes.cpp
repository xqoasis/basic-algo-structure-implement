#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// To execute C++, please define "int main()"
int main() {
  vector<int> numSeq = {3, 6, 2, 3, 5};

  deque<int> dq;

  for(auto i:numSeq){
    dq.push_back(i);
  }

  bool turn = false; // false: 1, true: 2
  bool rever = false;
  int p1 = 0, p2 = 0;
  int pre = 1;
  int cntscore;

  while (!dq.empty()){
    if (pre%2 == 0){
      rever = !rever;
      if (rever){
        cntscore = dq.back();
        dq.pop_back();    
      }else{
        cntscore = dq.front();
        dq.pop_front();
      }
    }else{
      if (rever){
        cntscore = dq.back();
        dq.pop_back();    
      }else{
        cntscore = dq.front();
        dq.pop_front();
      }
    }

    if (turn == false){    
      p1 += cntscore;
    }else{
      p2 += cntscore;
    }

    turn = !turn;
    //cout << p1<< ":"<< p2 << endl;
    pre = cntscore;
  }

  cout << p1 - p2;


  return 0;
}
