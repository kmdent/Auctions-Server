#ifndef SAGENT_H
#define SAGENT_H
#include "agent.h"

class sAgent: public Agent
{
public:
    sAgent(int i);
    virtual ~sAgent();
    vector<float> bidSimultaneous(int numGoods);
    float bidSequential(int numGoods, int round, vector<int> winners);
    bool firstPrice;
    float _bid;



};

#endif // SAGENT_H
