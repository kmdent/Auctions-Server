#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>

using namespace std;

class Agent
{
public:
    int numBidders;
    vector<int> highBidders;
    int ask;
    int id;
    vector<float> payments;
    bool isSuper;
    bool isSeq;
    vector<float> valuations;
    Agent(int i);
    float bid(float i);
    void createValuations(int numGoods);

protected:
};

#endif // AGENT_H
