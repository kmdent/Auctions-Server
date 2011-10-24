#include "dagent.h"
#include <iostream>

dAgent::dAgent(int ID) : Agent(ID)
{
}

dAgent::~dAgent(){

}

float dAgent::bid(float cur){
    /*if(valuation >= cur){
        _bid = cur;
        cout << "we want to bid: "<< valuation << " I am: "<< id << " My bid: " << _bid << endl;

    }else{
        _bid = 0;
    }*/
    return _bid;
}
