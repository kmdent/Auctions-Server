#include "sagent.h"

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

int sAgent::bid(int i){
    return i;
}
