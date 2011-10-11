#include "aagent.h"

aAgent::aAgent(int id) : Agent(id)
{

}

aAgent::~aAgent(){

}

int aAgent::bid(int ask){
    return ask;
}



