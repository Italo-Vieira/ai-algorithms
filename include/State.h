#ifndef STATE_H
#define STATE_H

template <class DataType>
class State
{
    public:
        State();
        virtual ~State();
        virtual bool GenerateChildrens()=0;
    protected:

    private:
        DataType    data;
};

#endif // STATE_H
