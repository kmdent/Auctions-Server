#include "aagent.h"

aAgent::aAgent(int id) : Agent(id)
{

}

aAgent::~aAgent(){

}

vector<float> aAgent::bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices){
    for(int i = 0; i<numGoods; i++){
        if(currWinners.at(i) != id && askPrices.at(i) < valuations.at(i)){
            bids.at(i) = askPrices.at(i);
        }
    }
    return bids;
}

float aAgent::bidSequential(int numGoods, int round, vector<int> winners, float winningPrice, float askPrice){
    if(winners.at(round) != id && askPrice < valuations.at(round)){
        bids.at(round) = askPrice;
    }
    return bids.at(round);
}


