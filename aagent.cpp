#include "aagent.h"
#include "price_predictor.h"
#include "iostream"

aAgent::aAgent(int id) : Agent(id)
{
round = 0;
prevAsk.push_back(0);
prevAsk.push_back(0);
prevAsk.push_back(0);
prevAsk.push_back(0);
prevAsk.push_back(0);
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

    priceVec.push_back(17.16);
    priceVec.push_back(11.79);
    priceVec.push_back(7.45);
    priceVec.push_back(4.46);
    priceVec.push_back(.807);


    //cout << "about to create the predictor" << endl;

   /* price_predictor * p = new price_predictor(tmpPrice,1, subsets);
    priceVec = p->getPrices();
    */

    //cout << "PriceVec: ";

   // for(int i = 0; i < priceVec.size(); i++){
    //cout << priceVec.at(i) << ",  ";
    //}



    //cout << "Prediction ended &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

}
vector<float> aAgent::bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices){
    //cout << "round: " << round <<endl;
    if(round == 0){
        predictPrice();
    }


    vector<float> perceivedPrices;
    for(int i = 0; i < numGoods; i++) {
        if (currWinners.at(i) == id)
            perceivedPrices.push_back(max(winningPrices.at(i),
                                          priceVec.at(i)));
        else
            perceivedPrices.push_back(max(askPrices.at(i),
                                          priceVec.at(i)));
    }

    if(!MV){
        for(int i = 0; i < askPrices.size(); i ++){
            if(askPrices.at(i) == prevAsk.at(i)){
                perceivedPrices.at(i) = askPrices.at(i);
            }
        }
        prevAsk = askPrices;
    }
    vector<int> * optBundle = optimalBundle(perceivedPrices);
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

vector<float> aAgent::bidSimultaneous(int numGoods, vector<int> currWinners, vector<float> winningPrices, vector<float> askPrices, vector<float> priceVec){

    vector<float> perceivedPrices;
    for(int i = 0; i < numGoods; i++) {
        if (currWinners.at(i) == id)
            perceivedPrices.push_back(max(winningPrices.at(i), priceVec.at(i)));
        else
            perceivedPrices.push_back(max(askPrices.at(i), priceVec.at(i)));
    }


    vector<int> * optBundle = optimalBundle(perceivedPrices);
    bids.clear();

    for(int i = 0; i < numGoods; i++) bids.push_back(0.0);

    for(int i = 0; i < optBundle->size(); i++) {
        int good = optBundle->at(i);
        if (currWinners.at(good - 1) != id)
            bids.at(good-1) = askPrices.at(good-1);
    }

   /* cout << "Agent: " << id << ", Lambda: " << lambda << ", Opt Bundle: ";
    for(int i = 0; i < optBundle->size(); i++){
        cout << optBundle->at(i) << ", AskPrice: " << askPrices.at(optBundle->at(i)-1) << " ";
    }
    cout << " Surplus: " << surplus(optBundle,perceivedPrices) << endl;
    */
    //string a;
    //cin >> a;

    //for(int i = 0; i<numGoods; i++){
    //    if(currWinners.at(i) != id && askPrices.at(i) < valuations.at(i)){
    //        bids.at(i) = askPrices.at(i);
    //    }
    //}
    round++;
    return bids;
}







