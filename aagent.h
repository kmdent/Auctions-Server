#ifndef AAGENT_H
#define AAGENT_H
#include "agent.h"

class aAgent: public Agent
{
public:
    aAgent(int i);
    virtual ~aAgent();
    float bid(float i);
};

#endif // AAGENT_H
