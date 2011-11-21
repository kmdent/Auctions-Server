#ifndef PRICE_PREDICTOR_H
#define PRICE_PREDICTOR_H
#include "agent.h"

class price_predictor
{
public:
    price_predictor(vector<float> predict,bool isA, vector< vector<int> *> * _subsets);
    virtual ~price_predictor();
    int numAgents;
    bool firstPrice;
    int highBidder;
    int numGoods;
    vector<Agent*> agents;


    void runAscending();
    void runSealedPrice();
    vector<float> getPrices();
    void clear_all();
    bool iteration(bool isA);
    void vector_divideEquals(vector<float> * v, float divisor);
    void vector_plusEquals(vector<float> * v1, vector<float> v2);

private:
    vector<float> PP;
    vector<float> *convPrice;
    vector<float> secondPrices;
    vector<int> highBidders;
    vector<float> winningPrices;
    vector<float> askPrices;

};
#endif // PRICE_PREDICTOR_H
