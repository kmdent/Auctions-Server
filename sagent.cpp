#include "sagent.h"
#include "iostream"

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

float sAgent::bid(int i){
    if(firstPrice){
        _bid = (((numBidders-1)*valuation)/numBidders);
    }else{
        _bid = valuation;
    }
    return _bid;
}
