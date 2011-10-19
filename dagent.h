#ifndef DAGENT_H
#define DAGENT_H
#include "agent.h"

class dAgent: public Agent
{
public:
    dAgent(int i);
    virtual ~dAgent();
    float bid(float i);
    float _bid;
};

#endif // DAGENT_H
