#include "SearchAlgorithms.h"

void SearchAlgorithms::removeEquals(list<State*> &from, list<State*> &in){
  #pragma omp parallel
  #pragma omp master
  for(iterator itf = from.begin(); itf != from.end(); itf++){
    #pragma omp task
    #pragma omp parallel
    #pragma omp single nowait
    for(iterator iti = in.begin(); iti != in.end(); iti++){
      if((*itf)->equals(*iti)){
        delete *itf;
        #pragma omp critical(removeFromList)
        itf = from.erase(itf);
        break;
      }
    }
  }
}

void SearchAlgorithms::freeList(list<State*> &toBeFreed){
  for(iterator it = toBeFreed.begin(); it != toBeFreed.end();){
     delete *it;
     it = toBeFreed.erase(it);
   }
}

Path* SearchAlgorithms::BFS(State *state){
  list<State*>  stateQueue;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateQueue.push_back(state);
  Path *path;
  while(!stateQueue.empty()){

    #ifdef _OPENMP
    int taskNum;
    #pragma omp parallel
    #pragma omp single
    {
      int queueSize = stateQueue.size();
      int num_threads = omp_get_team_size(omp_get_level());
      taskNum = (queueSize > num_threads) ? num_threads : queueSize;
    }

    #pragma omp for ordered
    for (int i = 0; i < taskNum; i++ ){
    #endif

    State *currentState ;
    #pragma omp ordered
    {
    currentState =  stateQueue.front();
    closedStates.splice(closedStates.end(),stateQueue,stateQueue.begin());
    }

    #pragma single
    if(currentState->isObjective()){
      std::cout<<"\nyoo\n";
      Path *path = new Path();
      while(currentState != 0){
        path->addNode(currentState);
        currentState = currentState->father;
      }
    }else{

    currentState->GenerateChildrens();
    childrens = currentState->childrens;

    #pragma omp ordered
    {
    removeEquals(childrens, stateQueue);
    removeEquals(childrens, closedStates);
    stateQueue.splice(stateQueue.end(), childrens);
    }
    }
    #ifdef _OPENMP
    }
    #endif
  }

  freeList(closedStates);
  freeList(stateQueue);
  return path;
}


Path* SearchAlgorithms::DFS(State *state){
  list<State*>  stateStack;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateStack.push_back(state);
  while(!stateStack.empty()){
    {
    State *currentState =  stateStack.front();
    stateStack.pop_front();
    closedStates.push_back(currentState);
    if(currentState->isObjective()){
      Path *path = new Path();
      std::cout<<"\nfound\n";
      while(currentState != 0){
        path->addNode(currentState);
        currentState = currentState->father;
      }

      freeList(closedStates);
      freeList(stateStack);
      return path;
    }

    currentState->GenerateChildrens();
    childrens = currentState->childrens;

    removeEquals(childrens, stateStack);
    removeEquals(childrens, closedStates);
    iterator a = stateStack.begin();
    stateStack.splice(a, childrens);
    }
  }

  freeList(closedStates);
  return 0;
}
