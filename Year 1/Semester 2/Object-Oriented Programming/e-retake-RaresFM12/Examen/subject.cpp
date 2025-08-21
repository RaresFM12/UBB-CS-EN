#include "subject.h"

void Subject::addObserver(Observer* obs)
{
    this->observers.push_back(obs);
}

void Subject::notify()
{
    for (Observer* o : observers)
        o->update();
}
