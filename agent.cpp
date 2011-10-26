#include "agent.h"
#include "stdio.h"
#include "iostream"



Agent::Agent(int tmp)
{
    id = tmp;
}

void Agent::createValuations(int numGoods){
    for(int i = 0; i < numGoods; i++){
        valuations.push_back(((float)rand()) / (float)(RAND_MAX));
        payments.push_back(0);
        bids.push_back(0);
    }
}

float Agent::bid(float i){
    return i;
}
