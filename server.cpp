#include "server.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "stdio.h"
#include "vector"
#include "agent.h"
#include "aagent.h"
#include "dagent.h"
#include "sagent.h"
#include <ctime>

using namespace std;
Server::Server()
{
}

Server::~Server()
{
}

void Server::runAscending(){
    bool isOver = false;

    for(int i = 0; i < numAgents; i++){
        agents.push_back(new aAgent(i));
        agents.at(i)->numBidders = numAgents;
        agents.at(i)->isSuper = isSuper;
        agents.at(i)->isSeq = isSequential;
    }

    while(!isOver){
        int askPrice = .05;
        for(int i = 0; i < agents.size(); i++){
            agents.at(i)->highBidders.at(0) = highBidder;
            agents.at(i)->bid(askPrice);
        }
    }
}

void Server::runDescending(){

    bool isOver = false;
    float currPrice = 1;
    float decrement = currPrice * .05;

    for(int i = 0; i < numAgents; i++){
        agents.push_back(new dAgent(i));
    }

   /* while(!isOver){
        for(int i = 0; i < numAgents; i++){
            float tmpBid = 0;
            tmpBid = ((dAgent*)agents.at(i))->bid(currPrice);
            if(tmpBid != 0){
                isOver = true;
                ((dAgent*)agents.at(i))->payment = tmpBid;
                break;
            }
        }
        cout <<"No bidders at: "<<currPrice << " , reducing the price to: " << (currPrice-decrement)<< endl;
        currPrice = currPrice- decrement;
    }
    for(int i = 0; i < numAgents; i++){
        //cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuations << ", Bid: " <<((dAgent*) agents.at(i))->_bid << ", Paid: "<< agents.at(i)->payment <<", Profit: " <<((dAgent*) agents.at(i))->valuation - ((dAgent *)agents.at(i))->payment <<"}"<<endl;
    }*/

}

void Server::runSealedPrice(){

    vector<vector<float> > bids;
    vector<int> winners;
    vector<float> highestBids;
    vector<float> secondPrices;

    for(int i = 0; i < numGoods; i++){
        winners.push_back(-1);
    }
    for(int i = 0; i < numAgents; i++){
        sAgent *s = new sAgent(i);
        s->createValuations(numGoods);
        s->numBidders = numAgents;
        s->firstPrice = firstPrice;
        agents.push_back(s);
    }

    if(! isSequential){ //simultaneous
        for(int i = 0; i < agents.size(); i++){
            bids.push_back(((sAgent*)(agents.at(i)))->bidSimultaneous(numGoods));
        }
        for(int good = 0; good < numGoods; good++){
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
            highestBids.push_back(highBid);
            secondPrices.push_back(secondBid);
        }
    }
    else{
        for(int i = 0; i < numAgents; i++){
            vector<float> v;
            bids.push_back(v);
        }
        for(int round = 0; round < numGoods; round ++){
            for(int i = 0; i < agents.size(); i++){
                bids.at(i).push_back(((sAgent*)(agents.at(i)))->bidSequential(numGoods, round, winners));
            }
            float highBid = 0;
            float secondBid = 0;
            for(int bidder = 0; bidder < agents.size(); bidder++){
                if(bids.at(bidder).at(round) > highBid){
                    secondBid = highBid;
                    highBid = bids.at(bidder).at(round);
                    winners.at(round) = bidder;
                }
                else if(bids.at(bidder).at(round) > secondBid){
                    secondBid = bids.at(bidder).at(round);
                }
            }
            highestBids.push_back(highBid);
            secondPrices.push_back(secondBid);
        }
    }

    cout << "-------------------------Auction Results__________________________"<<endl;
    for(int good = 0; good < numGoods; good++){
        cout << "Good " << good << endl;
        for(int bidder = 0; bidder < numAgents; bidder++){
            if(winners.at(good) == bidder){
                if(firstPrice){
                    agents.at(bidder)->payments.at(good) = highestBids.at(good);
                }
                else{
                    agents.at(bidder)->payments.at(good) = secondPrices.at(good);
                }
            }
            else agents.at(bidder)->payments.at(good) = 0;
        }
        for(int i = 0; i < numAgents; i++){
            cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuations.at(good) << ", Bid: " << bids.at(i).at(good) << ", Paid: "<< agents.at(i)->payments.at(good) << "}"<<endl;
        }
    }
}

int main(int argc, char *argv[]){

    string aType;
    string super;
    string seq;
    string price;
    string goods;
    Server * server= new Server();
    server->numGoods = 1;
    srand(time(NULL));
    rand();
    cout << "Enter the type of Auction" << endl;
    cin >> aType;

    cout << "Is this a Super auction?" << endl;
    cin >> super;
    if(super == "yes"){
        server->isSuper = true;
        cout << "How many goods?" << endl;
        cin >> goods;
        server->numGoods = atoi(goods.c_str());
    }else{
        server->isSuper = false;
    }

    cout << "Is this a sequential auction?" << endl;
    cin >> seq;
    if(!seq.compare("yes")){
        server->isSequential = true;
    }else{
        server->isSequential = false;
    }

    cout << "Enter the number of Bidders" << endl;
    cin >> server->numAgents;

    if(!aType.compare("Ascending") || !aType.compare("A")){
        cout << "running ascending" << endl;
        server->runAscending();
    }else if(!aType.compare("Descending")|| !aType.compare("D")){
        server->runDescending();
    }else if(!aType.compare("Sealed") || !aType.compare("S")){
        cout << "1st or 2nd price?" << endl;
        cin >> price;
        if(! price.compare("1st")){
            server->firstPrice = true;
        }
        else server->firstPrice = false;
        server->runSealedPrice();
    }

    delete server;
    return 1;

}

