#include "SearchAlgorithm.h"

void SearchAlgorithm::removeEquals(list<State*> &from, list<State*> &in){
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

void SearchAlgorithm::freeList(list<State*> &toBeFreed){
  for(iterator it = toBeFreed.begin(); it != toBeFreed.end(); it = toBeFreed.erase(it));
}

Path* SearchAlgorithm::BFS(State *state){
  list<State*>  stateQueue;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateQueue.push_back(state);
  while(!stateQueue.empty()){
    State *currentState =  stateQueue.front();
    stateQueue.pop_front();
    if(currentState->isObjective()){
      Path *path = new Path();
      while(currentState != 0){
        path->addNode(currentState);
        currentState = currentState->father;
      }

      freeList(closedStates);
      freeList(stateQueue);
      return path;
    }
    currentState->GenerateChildrens();
    childrens = currentState->childrens;
    removeEquals(childrens, stateQueue);
    removeEquals(childrens, closedStates);

    stateQueue.splice(stateQueue.end(), childrens);
    closedStates.push_back(currentState);
  }

  freeList(closedStates);

  return 0;
}


Path* SearchAlgorithm::DFS(State *state){
  list<State*>  stateStack;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateStack.push_back(state);
  while(!stateStack.empty()){
    State *currentState =  stateStack.front();
    stateStack.pop_front();
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
    closedStates.push_back(currentState);

  }

  freeList(closedStates);
  return 0;
}
