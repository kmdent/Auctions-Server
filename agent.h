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
    Agent(int);
    int bid(int);
};

#endif // AGENT_H
