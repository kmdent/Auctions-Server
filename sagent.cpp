#include "sagent.h"
#include "iostream"

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

vector<float> sAgent::bidSimultaneous(int numGoods){
    vector<float> v;
    for(int i = 0; i < numGoods; i++){
        if(firstPrice){
            v.push_back((valuations.at(i)*(numBidders-1)) / (float)numBidders);
        }
        else v.push_back(valuations.at(i));
    }
    return v;
}

float sAgent::bidSequential(int numGoods, int round, vector<int> winners){
    if(firstPrice){
        return valuations.at(round)*(numBidders-1) / (float)numBidders;
    }
    else return valuations.at(round);
}
