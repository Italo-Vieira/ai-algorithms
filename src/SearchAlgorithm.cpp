#include "SearchAlgorithm.h"



void SearchAlgorithm::removeEquals(list<State*> &from, list<State*> &in){
  for(list<State*>::iterator itf = from.begin(); itf != from.end(); itf++){
    for(list<State*>::iterator iti = in.begin(); iti != in.end(); iti++){
      if((*itf)->equals(*iti)){
        itf = from.erase(itf);
        break;
      }
    }
  }
}

State* SearchAlgorithm::BFS(State *state){
  list<State*>  stateQueue;
  list<State*>  closedStates;
  list<State*>  childrens;
  stateQueue.push_back(state);
  while(!stateQueue.empty()){
    State *currentState =  stateQueue.front();
    stateQueue.pop_front();
    if(currentState->isObjective()){
      std::cout<<"Found\n";
      return currentState;
    }
    currentState->GenerateChildrens();
    childrens = currentState->childrens;
    removeEquals(childrens, stateQueue);
    removeEquals(childrens, closedStates);

    stateQueue.splice(stateQueue.end(), childrens);
    closedStates.push_back(currentState);

  }
}
