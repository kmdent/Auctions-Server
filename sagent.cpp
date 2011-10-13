#include "sagent.h"
#include "iostream"

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

float sAgent::bid(int i){
    if(firstPrice){
        return (((numBidders-1)*valuation)/numBidders);
    }
    else return valuation;
}
