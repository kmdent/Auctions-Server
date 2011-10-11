#ifndef DAGENT_H
#define DAGENT_H
#include "agent.h"

class dAgent: public Agent
{
public:
    dAgent(int i);
    virtual ~dAgent();
    int bid(int i);
};

#endif // DAGENT_H
