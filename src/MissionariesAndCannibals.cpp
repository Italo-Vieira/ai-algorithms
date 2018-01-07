#include <iostream>
#include "SearchAlgorithms.h"

#define NMISS 10000
#define NCANN 10000
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
  if(NCANN-cann > NMISS-miss && NMISS-miss!=0){
    return 0;
  }
  if(cann < 0 || miss < 0)
    return 0;
  if(cann > NCANN || miss > NMISS || boat > 1)
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
/*  MissAndCannState* a=new MissAndCannState(NMISS,NCANN,1,0);
  SearchAlgorithms::BFS((State*)a);
   a=new MissAndCannState(NMISS,NCANN,1,0);
  SearchAlgorithms::DFS((State*)a);*/

  /*sem_t* sem = (sem_t*) malloc(sizeof(sem_t));
  sem_init(sem,0,1);
  {
    int j=1,k=10;
    #pragma omp parallel private(j)
    while(j++,j<k){
      #pragma omp single nowait
      for(int i = 0; i< 1 ; i++){
        for(int h = 0;h<4000;h++);
        #pragma omp critical
        {
        //  sem_wait(sem);
          std::cout<<j<<"ha "<<omp_get_thread_num();
          std::cout<<"\n";

        }
      }

    }
  }
  int i=0;
  int k=10;
  #pragma omp parallel
  #pragma omp master
  while(i<k){
    #pragma omp task
    #pragma omp parallel
    #pragma omp single nowait
    {
      #pragma omp critical
      std::cout<<"oi "<<i<<"\n";
    }
    i++;
  }*/
  
}
