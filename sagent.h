#ifndef SAGENT_H
#define SAGENT_H
#include "agent.h"
#include "string"

class sAgent: public Agent
{
public:
    sAgent(int i);
    virtual ~sAgent();
    vector<float> bidSimultaneous(int numGoods, vector<float> prediction, bool isPrediction);
    bool firstPrice;
    float _bid;



};

#endif // SAGENT_H
