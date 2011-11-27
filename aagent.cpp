#include "aagent.h"
#include "price_predictor.h"
#include "iostream"

aAgent::aAgent(int id) : Agent(id)
{


}

aAgent::~aAgent(){

}

void aAgent::predictPrice(){
    vector<float> tmpPrice;
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);
    tmpPrice.push_back(10);

    price_predictor * p = new price_predictor(tmpPrice,1, subsets);
    priceVec = p->getPrices();
    cout << "Prediction ended &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

}
vector<float> aAgent::bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices){

    if(round == 0){
        predictPrice();
    }

    /*CODE THE LOGIC HERE*/
    vector<float> perceivedPrices;
    for(int i = 0; i < numGoods; i++) {
        if (currWinners.at(i) == id)
            perceivedPrices.push_back(max(winningPrices.at(i), priceVec.at(i)));
        else
            perceivedPrices.push_back(max(askPrices.at(i), priceVec.at(i)));
    }


    vector<int> * optBundle = optimalBundle(priceVec);
    bids.clear();

    for(int i = 0; i < numGoods; i++) bids.push_back(0.0);

    for(int i = 0; i < optBundle->size(); i++) {
        int good = optBundle->at(i);
        if (currWinners.at(good - 1) != id)
            bids.at(good -1) = askPrices.at(good-1);
    }


    //for(int i = 0; i<numGoods; i++){
    //    if(currWinners.at(i) != id && askPrices.at(i) < valuations.at(i)){
    //        bids.at(i) = askPrices.at(i);
    //    }
    //}
    round++;
    return bids;
}

vector<float> aAgent::bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices, vector<float> priceVec){

    vector<float> perceivedPrices;
    for(int i = 0; i < numGoods; i++) {
        if (currWinners.at(i) == id)
            perceivedPrices.push_back(max(winningPrices.at(i), priceVec.at(i)));
        else
            perceivedPrices.push_back(max(askPrices.at(i), priceVec.at(i)));
    }


    vector<int> * optBundle = optimalBundle(priceVec);
    bids.clear();

    for(int i = 0; i < numGoods; i++) bids.push_back(0.0);

    for(int i = 0; i < optBundle->size(); i++) {
        int good = optBundle->at(i);
        if (currWinners.at(good - 1) != id)
            bids.at(good-1) = askPrices.at(good-1);
    }


    //for(int i = 0; i<numGoods; i++){
    //    if(currWinners.at(i) != id && askPrices.at(i) < valuations.at(i)){
    //        bids.at(i) = askPrices.at(i);
    //    }
    //}
    round++;
    return bids;
}







