#include "agent.h"
#include "stdio.h"
#include "iostream"



Agent::Agent(int tmp)
{
    id = tmp;
    valuation = ((float)rand() / (float)(RAND_MAX));
    payment = 0;
}

float Agent::bid(float i){
    return i;
}
