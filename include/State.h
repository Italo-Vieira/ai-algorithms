#ifndef STATE_H
#define STATE_H
#include <list>
using std::list;
template <class DataType>
class State
{
    public:
        State();
        virtual ~State();
        virtual bool GenerateChildrens()=0;
        virtual float getHeuristcValue()=0;
        virtual float getStateWeight()=0;
        virtual bool isObjective()=0;
    protected:

    private:
        DataType        data;
        list<DataType>  childrens;
        int             childrensCount;

};

#endif // STATE_H
