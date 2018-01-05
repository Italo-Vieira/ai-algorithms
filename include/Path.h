#include "State.h"

class Path{
  public:
    Path();
    void addNode(State* node){
      path.push_front(node);
      totalWeight += node->getStateWeight();
      nodeCount++;
    }
  private:
    list<State*> path;
    float totalWeight;
    int nodeCount;
};
