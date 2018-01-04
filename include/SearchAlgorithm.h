#include <iostream>
#include "State.h"

class SearchAlgorithm{
  public:
    static bool BFS(State*);
  private:
    static void removeEquals(list<State*> &from, list<State*> &in);
};
