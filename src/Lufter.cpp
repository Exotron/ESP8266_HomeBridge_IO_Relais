#include "Lufter.h"

int Lufter::getState()
{
    return this->state;
}
bool Lufter::setState(int state)
{
    this->state = state;
    return true;
}
Lufter::Lufter()
{
    this->setState(0);
}