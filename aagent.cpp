#include "aagent.h"

aAgent::aAgent(int id) : Agent(id)
{

}

aAgent::~aAgent(){

}

float aAgent::bid(float ask){
    return ask;
}



