#ifndef STATE_H
#define STATE_H

#ifdef _OPENMP
#include <omp.h>
#endif

#include <list>
using std::list;
class SearchAlgorithms;
class State
{
  friend class SearchAlgorithms;
  public:
    State(State* father){this->father = father;delflag=true;};
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
    bool delflag;
    State* father;
    list<State*> childrens;
};

#endif // STATE_H
