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
      //found solution
      Path *path = new Path();
      //create a path from found soluction
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
    iterator currIt = stateStack.begin();
    State *currentState =  *currIt;

    if(currentState->isObjective()){
      Path *path = new Path();
      while(currentState != 0){
        path->addNode(currentState);
        stateStack.erase(currIt);
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
    iterator a = stateStack.begin();
    stateStack.splice(a, childrens);
  }
  std::cout<<"saiu";

  freeList(closedStates);
  return 0;
}
