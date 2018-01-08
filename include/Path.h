#include "State.h"

class Path{
  public:
    Path();
    void addNode(State* node){
      path.push_back(node);
      totalWeight += node->getStateWeight();
      nodeCount++;
    }
    State* getObjective(){
      return *path.begin();
    }
  private:
    list<State*> path;
    float totalWeight;
    int nodeCount;
};
