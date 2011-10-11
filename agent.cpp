#include "agent.h"

Agent::Agent(int tmp)
{
    id = tmp;
    valuation = (rand() / RAND_MAX);
}

int Agent::bid(int i){
    return i;
}
