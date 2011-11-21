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
    int lambda;
    bool firstPrice;

    vector<float> bundleVal;
    vector<float> payments;
    vector<float> valuations;
    vector<float> bids;
    vector<vector<int> * > *  subsets;
    vector<int> goodsWon;

    Agent(int i);
    float bid(float i);
    void createValuations(vector<vector<int> * > *  subsets_,int numGoods);
    int getBundleValue(vector<int> *  subset);
    float surplus(vector<int> * subset, vector<float> priceVecb);
    vector<int> * optimalBundle(vector<float> priceVec);
    float marginalValue(int good, vector<float> priceVec);
protected:
};

#endif // AGENT_H
