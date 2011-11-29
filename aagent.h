#ifndef AAGENT_H
#define AAGENT_H
#include "agent.h"

class aAgent: public Agent
{
public:
    aAgent(int i);
    vector<float> priceVec;
    vector<float> prevAsk;
    int round;
    int MV;
    void predictPrice();
    virtual ~aAgent();
    vector<float> bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices);
    vector<float> bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices, vector<float> priceVec);

};

#endif // AAGENT_H
