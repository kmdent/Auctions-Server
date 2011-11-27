#include "price_predictor.h"
#include "stdlib.h"
#include "stdio.h"
#include "vector"
#include "agent.h"
#include "aagent.h"
#include "sagent.h"
#include "iostream"
#include <ctime>
#include <cmath>

using namespace std;


/*GLOBALS*/
vector<vector<int> * > * Psubsets;


void price_predictor::runAscending(){
    bool isOver = false;
    vector<vector<float> > bids;
    vector<int> winners;
    vector<float> highestBids;
    vector<float> secondPrices;
    vector<float> winningPrices;
    vector<float> askPrices;
    vector<int> quiescent;

    for(int i = 0; i < numGoods; i++){
        highestBids.push_back(0);
        secondPrices.push_back(0);
        winners.push_back(-1);
        winningPrices.push_back(0);
        askPrices.push_back(.05);
        quiescent.push_back(0);
    }
    for(int i = 0; i < numAgents; i++){
        aAgent *a = new aAgent(i);
        a->createValuations(Psubsets, numGoods);
        a->numBidders = numAgents;
        a->firstPrice = firstPrice;
        agents.push_back(a);
    }

    while(! isOver){
        bids.clear();
        for(int i = 0; i < agents.size(); i++){
            bids.push_back(((aAgent*)(agents.at(i)))->bidSimultaneous(numGoods, winners, winningPrices, askPrices, PP));
        }


        for(int good = 0; good < numGoods; good++){
            quiescent.at(good) = 1;
            vector<int> ties;
            for(int bidder = 0; bidder < agents.size(); bidder++){
                if(bids.at(bidder).at(good) >= askPrices.at(good)){
                    if(bids.at(bidder).at(good) > highestBids.at(good)){
                        secondPrices.at(good) = highestBids.at(good);
                        highestBids.at(good) = bids.at(bidder).at(good);
                        ties.clear();
                        ties.push_back(bidder);
                        quiescent.at(good) = 0;
                    }
                    else if(bids.at(bidder).at(good) == highestBids.at(good)){
                        ties.push_back(bidder);
                        secondPrices.at(good) = bids.at(bidder).at(good);
                    }
                    else if(bids.at(bidder).at(good) > secondPrices.at(good)){
                        secondPrices.at(good) = bids.at(bidder).at(good);
                    }
                }
            }
            if(ties.size() > 0){
                int randWinner = (int)(((float)rand() / (float)(RAND_MAX)) * ties.size());
                winners.at(good) = ties.at(randWinner);
            }
            if(firstPrice){
                winningPrices.at(good) = highestBids.at(good);
            }
            else winningPrices.at(good) = secondPrices.at(good);
            askPrices.at(good) = highestBids.at(good)+.05;

        }

        // Round is over

        isOver = true;
        for(int i = 0; i< numGoods; i++){
            if(quiescent.at(i) == 0){
                isOver = false;
                break;
            }
        }
    }
}


void price_predictor::runSealedPrice(){

    vector<vector<float> > bids;
    vector<int> winners;
    vector<float> highestBids;

    for(int i = 0; i < numGoods; i++){
        winners.push_back(-1);
    }
    for(int i = 0; i < numAgents; i++){
        sAgent *s = new sAgent(i);
        if(1){
            s->MV = 1;
        }else{
            s->MV = 0;
        }
        s->createValuations(Psubsets,numGoods);
        s->numBidders = numAgents;
        s->firstPrice = firstPrice;
        agents.push_back(s);
    }


    for(int i = 0; i < agents.size(); i++){
        bids.push_back(((sAgent*)(agents.at(i)))->bidSimultaneous(numGoods, PP, 0 ));
    }
    for(int good = 0; good < numGoods; good++){ // Iterating the goods
        float highBid = 0;
        float secondBid = 0;

        for(int bidder = 0; bidder < agents.size(); bidder++){
            if(bids.at(bidder).at(good) > highBid){
                secondBid = highBid;
                highBid = bids.at(bidder).at(good);
                winners.at(good) = bidder;
            }
            else if(bids.at(bidder).at(good) > secondBid){
                secondBid = bids.at(bidder).at(good);
            }
        }
        if(winners.at(good) == -1){
            winners.at(good) = (int)(((float)rand() / (float)(RAND_MAX))*numAgents);
        }
        highestBids.push_back(highBid);
        secondPrices.push_back(secondBid);
       // cout << good << " " << winners.at(good) << endl;
        agents.at(winners.at(good))->goodsWon.push_back(good +1); /*Sets up the goods won array*/
    }
    //return secondPrices;

}

vector<float> price_predictor::getPrices(){
    return *convPrice;
}

price_predictor::~price_predictor(){


}
void price_predictor::clear_all(){
    highBidder =0;

    agents.clear();
    secondPrices.clear();
    highBidders.clear();
    winningPrices.clear();
    askPrices.clear();

}

bool price_predictor::iteration(bool isA){

    vector<float> averagePrice;
    for (int i = 0; i < numGoods; i++) averagePrice.push_back(0.0); /*Init the vector*/

    for(int i = 0; i < 1000; i++){
        clear_all();
        if(isA){
            runAscending();

        }else{
            runSealedPrice();
        }
        vector_plusEquals(&averagePrice, secondPrices);
    }
    vector_divideEquals(&averagePrice, (float)1000.0);


    /*Do the convergence bullshit*/
    bool converged = true;
    for(int i = 0; i < convPrice->size(); i++){
        if (fabs(convPrice->at(i) - averagePrice.at(i)) > .1) {
            converged = false;
            break;
        }
    }
    *convPrice = averagePrice;
    clear_all();
    return converged;
}



price_predictor::price_predictor(vector<float> _predict,bool isA, vector< vector<int> *> * _subs)
{
    convPrice = new vector<float>(5);
    Psubsets = _subs;
    PP = _predict;
    srand(time(NULL));
    rand();

    firstPrice = false;
    numGoods = 5;
    numAgents = 8;

    for(int i =0; i < 100; i++){
        bool converged = iteration(isA);
        cout << i << " iteration completed "  << endl;
        cout << "1:" << convPrice->at(0) << " 2:" << convPrice->at(1) << " 3:"
             << convPrice->at(2) << " 4:" << convPrice->at(3) << " 5:" << convPrice->at(4) << endl;
        PP.clear();
        PP = *convPrice;
        if(converged){
            break;
        }
    }


}

void price_predictor::vector_plusEquals(vector<float> * v1, vector<float> v2) {

    for (int i = 0; i < v1->size(); i++) {
        v1->at(i) += v2.at(i);
    }
}

void price_predictor::vector_divideEquals(vector<float> * v, float divisor) {
    for (int i = 0; i < v->size(); i++) {
        v->at(i) /= divisor;
    }
}


