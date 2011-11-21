#include "sagent.h"
#include "iostream"
#include "price_predictor.h"

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

vector<float> sAgent::bidSimultaneous(int numGoods, vector<float> prediction,bool isPrediction){
    vector<float> v;
    vector<float> tmpPrice;
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);


    if(isPrediction == 1){
        price_predictor * p = new price_predictor(tmpPrice,0, subsets);
        prediction = p->getPrices();
        cout << "Prediction ended &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
    }

    for(int i = 0; i < numGoods; i++){
        float tmpbid = marginalValue(i+1,prediction);
        v.push_back(tmpbid);
    }
    return v;
}

