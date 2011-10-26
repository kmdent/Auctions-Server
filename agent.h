#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>

using namespace std;

class Agent
{
public:
    int numBidders;
    int id;
    vector<float> payments;
    bool firstPrice;
    vector<float> valuations;
    vector<float> bids;
    Agent(int i);
    float bid(float i);
    void createValuations(int numGoods);

protected:
};

#endif // AGENT_H
