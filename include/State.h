#ifndef STATE_H
#define STATE_H
#include <list>
using std::list;
class SearchAlgorithm;
class State
{
  friend class SearchAlgorithm;
  public:
    State(State* father){this->father = father;};
    virtual ~State(){};
    virtual float getHeuristicValue(){return 1;};
    virtual float getStateWeight(){return 1;};
    virtual bool equals(State*)=0;
    State* getFather(){ return father;}

  protected:
    virtual void GenerateChildrens()=0;
    virtual bool isObjective()=0;
    void addChildren(State* children){ childrens.push_back(children);};
  private:
    State* father;
    list<State*> childrens;
};

#endif // STATE_H
