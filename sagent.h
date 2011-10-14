#ifndef SAGENT_H
#define SAGENT_H
#include "agent.h"

class sAgent: public Agent
{
public:
    sAgent(int i);
    virtual ~sAgent();
    float bid(int i);
    bool firstPrice;
    float _bid;

};

#endif // SAGENT_H
