#include <iostream>
#include "State.h"
#include "Path.h"
typedef list<State*>::iterator iterator;
class SearchAlgorithm{
  public:
    static Path* BFS(State*);
    static Path* DFS(State*);
  private:
/*
Remove from 'from' any state that is also present in 'in'
*/
    static void removeEquals(list<State*> &from, list<State*> &in);
    static void freeList(list<State*>&);
};
