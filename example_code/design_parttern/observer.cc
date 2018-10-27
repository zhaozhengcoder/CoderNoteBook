#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OBSERVERABLE;

class OBSERVER
{
    private:
        OBSERVERABLE * _subject;
    public:
        void observe(OBSERVERABLE * subject);
        ~OBSERVER();
        virtual void update() = 0;
};

class OBSERVERABLE
{
    private:
        vector<OBSERVER *> _observers;
    public:
        void notify();
        void myregister(OBSERVER * observer);
        void unregister(OBSERVER * observer);
};

void OBSERVER::observe(OBSERVERABLE * subject)
{
    _subject = subject;
    _subject->myregister(this);    
}

OBSERVER::~OBSERVER()
{
    _subject->unregister(this);
}

void OBSERVERABLE::notify()
{
    for(int i=0;i<_observers.size();i++)
    {
        _observers[i]->update();
    }    
}

void OBSERVERABLE::myregister(OBSERVER * observer)
{
    _observers.push_back(observer);    
}

void OBSERVERABLE::unregister(OBSERVER * observer)
{
    auto iter = find(_observers.begin(),_observers.end(),observer);
    if(iter != _observers.end())
    {
        swap( *iter, _observers.back());
        _observers.pop_back();
    }    
}

class TEST_OBSERVER : public OBSERVER
{
public:
    virtual void update()
    {
        cout<<"foo update"<<endl;
    }
};

int main()
{
    TEST_OBSERVER * t = new TEST_OBSERVER;
    OBSERVERABLE subject;
    t->observe(&subject);

    subject.notify();

    delete t;
    subject.notify();

    return 0;
}