#ifndef SERVER_H
#define SERVER_H

#include "agent.h"
#include "vector"
class Server
{
public:
    int numAgents;
    bool isSequential;
    bool firstPrice;
    int highBidder;
    int numGoods;
    vector<Agent*> agents;



    Server();
    virtual ~Server();
    float runAscending();
    void runDescending();
    float runSealedPrice();

private:
    vector<int> highBidders;
    vector<float> winningPrices;
    vector<float> askPrices;

};

#endif // SERVER_H
