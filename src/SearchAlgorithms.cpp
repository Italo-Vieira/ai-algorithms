#include "SearchAlgorithms.h"

void SearchAlgorithms::removeEquals(list<State*> &from, list<State*> &in){
  #pragma omp parallel
  #pragma omp master
  for(iterator itf = from.begin(); itf != from.end();){
    iterator aux = itf++;
    #pragma omp task
    #pragma omp parallel private(itf)
    #pragma omp single nowait
    for(iterator iti = in.begin(); iti != in.end(); iti++){

      if((*aux)->equals(*iti)){
        delete *aux;
        #pragma omp critical(removeFromList)
        aux = --from.erase(aux);
        iti = --in.end();
      }
    }

  }
}

void SearchAlgorithms::freeList(list<State*> &toBeFreed){
  for(iterator it = toBeFreed.begin(); it != toBeFreed.end();){
    if((*it)->delflag)
     delete *it;
    it = toBeFreed.erase(it);
   }
}

Path* SearchAlgorithms::BFS(State *state){
  list<State*>  StateQueue;
  list<State*>  closedStates;
  list<State*>  childrens;
  StateQueue.push_back(state);

  while(!StateQueue.empty()){
    State *currentState =  StateQueue.front();

    if(currentState->isObjective()){
      Path *path = new Path();
      while(currentState != 0){
        path->addNode(currentState);
        currentState->delflag = false;
        currentState = currentState->father;
      }

      freeList(closedStates);
      freeList(StateQueue);
      return path;
    }

    StateQueue.pop_front();
    closedStates.push_back(currentState);
    currentState->GenerateChildrens();
    childrens = currentState->childrens;

    removeEquals(childrens, StateQueue);
    removeEquals(childrens, closedStates);
    StateQueue.splice(StateQueue.end(), childrens);
  }

  freeList(closedStates);
  return 0;
}


Path* SearchAlgorithms::DFS(State *state){
  list<State*>  stateStack;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateStack.push_back(state);

  while(!stateStack.empty()){
    State *currentState =  stateStack.front();

    if(currentState->isObjective()){
      Path *path = new Path();
      while(currentState != 0){
        path->addNode(currentState);
        currentState->delflag = false;
        currentState = currentState->father;
      }

      freeList(closedStates);
      freeList(stateStack);
      return path;
    }

    stateStack.pop_front();
    closedStates.push_back(currentState);
    currentState->GenerateChildrens();
    childrens = currentState->childrens;

    removeEquals(childrens, stateStack);
    removeEquals(childrens, closedStates);
    stateStack.splice(stateStack.begin(), childrens);
  }

  freeList(closedStates);
  return 0;
}
