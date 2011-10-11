#include "dagent.h"

dAgent::dAgent(int ID) : Agent(ID)
{
}

dAgent::~dAgent(){

}

int dAgent::bid(int i){
    return i;
}
