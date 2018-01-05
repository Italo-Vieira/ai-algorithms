#include <iostream>
#include "SearchAlgorithm.h"

class MissAndCannState:public State{
public:
  //On the wrong side
  int missionaries;
  int cannibals;
  int boat;

  MissAndCannState(int,int,int,MissAndCannState*);
protected:
  void GenerateChildrens();
  bool equals(State* MissAndCannState);
  bool isObjective();

private:
  int testAndAdd(int,int,int);
};

MissAndCannState::MissAndCannState(int miss, int cann,int boat,MissAndCannState* father):State(father){
  missionaries=miss;
  cannibals=cann;
  this->boat=boat;
}

void MissAndCannState::GenerateChildrens(){
  if(boat==1){//boat is on the left side
    testAndAdd(missionaries-2,cannibals,boat-1);
    testAndAdd(missionaries-1,cannibals-1,boat-1);
    testAndAdd(missionaries,cannibals-2,boat-1);
    testAndAdd(missionaries-1,cannibals,boat-1);
    testAndAdd(missionaries,cannibals-1,boat-1);

  }else{
    testAndAdd(missionaries+2,cannibals,boat+1);
    testAndAdd(missionaries+1,cannibals+1,boat+1);
    testAndAdd(missionaries,cannibals+2,boat+1);
    testAndAdd(missionaries+1,cannibals,boat+1);
    testAndAdd(missionaries,cannibals+1,boat+1);
    }
}

int MissAndCannState::testAndAdd(int miss,int cann,int boat){
  if(cann>miss && miss!=0)
    return 0;
  if(3-cann > 3-miss && 3-miss!=0){
    return 0;
  }
  if(cann < 0 || miss < 0)
    return 0;
  addChildren(new MissAndCannState(miss,cann,boat,this));
  return true;
}
bool MissAndCannState::equals(State* state){
  MissAndCannState* macstate = (MissAndCannState*) state;
  bool ret = true;
  ret = ret && (missionaries == macstate->missionaries);
  ret = ret && (cannibals == macstate->cannibals);
  ret = ret && (boat == macstate->boat);
  return ret;
}
bool MissAndCannState::isObjective(){
  return !(missionaries+cannibals+boat);
}

main(){
  MissAndCannState* a=new MissAndCannState(3,3,1,0);
  SearchAlgorithm::BFS((State*)a);

}
