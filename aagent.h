#ifndef AAGENT_H
#define AAGENT_H
#include "agent.h"

class aAgent: public Agent
{
public:
    aAgent(int i);
    virtual ~aAgent();
    vector<float> bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices);
    float bidSequential(int numGoods, int round, vector<int> winners, float winningPrice, float askPrice);
};

#endif // AAGENT_H
