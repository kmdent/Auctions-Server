#include "agent.h"
#include "stdio.h"
#include "iostream"



Agent::Agent(int tmp)
{
    id = tmp;
}

bool mysort(int i,int j){
    return (i>j);
}

void Agent::createValuations(vector<vector<int> * > *  subsets_, int numGoods){
    subsets = subsets_;
    lambda = (int) ((((float)rand()) / (float)(RAND_MAX))*numGoods)+1;
    for(int i = 0; i < numGoods; i++){
        int curVal = (int) ((((float)rand()) / (float)(RAND_MAX))*50)+1;
        valuations.push_back(curVal);
        payments.push_back(0);
        bids.push_back(0);
    }
    sort(valuations.begin(),valuations.end(), mysort);
    for(int i = 0; i < subsets->size(); i++){
        bundleVal.push_back(getBundleValue(subsets->at(i)));
    }
}

int Agent::getBundleValue(vector<int> *  subset){
    if(lambda > subset->size()){
        return 0;
    }else{
        return valuations.at(subset->at(lambda-1)-1);
    }
}

float Agent::surplus(vector<int> * subset, vector<float> priceVec){
    float total = 0.0;
    for(int i = 0; i < subset->size(); i++){
        total += priceVec.at(subset->at(i)-1);
    }
    return (getBundleValue(subset) - total);

}


vector<int> * Agent::optimalBundle(vector<float> priceVec) {
    vector<int> * optBundle;
    float maxSurplus = -1000000.0;

    for (int i = 0; i < subsets->size(); i++) {
        vector<int> * bundle = subsets->at(i);
        float surp = surplus(bundle, priceVec);
        if (surp > maxSurplus) {
            maxSurplus = surp;
            optBundle = bundle;
        }

    }
    return optBundle;

}



/*
 Find the difference between the surplus with the good set to zero and infinity
 This is essentially the straight MV method.
*/
float Agent::marginalValue(int good, vector<float> priceVec) {

    //cout << good <<" " <<  priceVec.size() << endl;

    priceVec.at(good-1) = 0;
    float surpWith = surplus(optimalBundle(priceVec), priceVec);

    priceVec.at(good-1) = 1000000000;
    float surpWO = surplus(optimalBundle(priceVec), priceVec);

    return surpWith - surpWO; /*Possibly subtract the price at good i*/
}





float Agent::bid(float i){
    cout << "THIS SHOULD NEVER BE HIT. IT IS THE GENERAL AGENTS BIDDING STRAT" << endl;
    return i;
}
