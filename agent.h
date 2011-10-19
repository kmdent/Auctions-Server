#ifndef AGENT_H
#define AGENT_H

#include <string>

using namespace std;

class Agent
{
public:
    int numBidders;
    int highBid;
    int ask;
    int id;
    float payment;
    bool isSuper;
    bool isSeq;
    float valuation;
    Agent(int i);
    float bid(float i);

protected:
};

#endif // AGENT_H
