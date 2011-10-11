#ifndef SAGENT_H
#define SAGENT_H
#include "agent.h"

class sAgent: public Agent
{
public:
    sAgent(int i);
    virtual ~sAgent();
    int bid(int i);
};

#endif // SAGENT_H
