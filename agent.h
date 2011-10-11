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
    bool isSuper;
    bool isSeq;
    Agent(int i);
    virtual int bid(int i);

private:
    int valuation;
};

#endif // AGENT_H
