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
            agents.at(i)->highBid = highBidder;
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

    while(!isOver){
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
        cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuation << ", Bid: " <<((dAgent*) agents.at(i))->_bid << ", Paid: "<< agents.at(i)->payment <<", Profit: " <<((dAgent*) agents.at(i))->valuation - ((dAgent *)agents.at(i))->payment <<"}"<<endl;
    }

}

void Server::runSealedPrice(){

    vector<float> prices;
    float highestBid = 0;
    float secondPrice = 0;
    highBidder = 0;

    for(int i = 0; i < numAgents; i++){
        agents.push_back(new sAgent(i));
        agents.at(i)->numBidders = numAgents;
        ((sAgent*)(agents.at(i)))->firstPrice = firstPrice;
    }
    for(int i = 0; i < agents.size(); i++){
        prices.push_back(((sAgent*)(agents.at(i)))->bid(0));
    }
    for(int i = 0; i < agents.size(); i++){
        if(prices.at(i) > highestBid){
            highestBid = prices.at(i);
            highBidder = i;
        }
        else if(prices.at(i) > secondPrice){
            secondPrice = prices.at(i);
        }
    }
    cout << "-------------------------Auction Results__________________________"<<endl;
    cout << "highest bidder: " << highBidder << endl;
    cout << "highest bid: " << highestBid << endl;
    for(int i = 0; i<agents.size(); i++){
        if(i == highBidder){
            if(firstPrice){
                agents.at(i)->payment = highestBid;
            }
            else agents.at(i)->payment = secondPrice;
        }
        else agents.at(i)->payment = 0;
    }
    for(int i = 0; i < numAgents; i++){
        cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuation << ", Bid: " <<((sAgent*) agents.at(i))->_bid << ", Paid: "<< agents.at(i)->payment << "}"<<endl;
    }

}

int main(int argc, char *argv[]){


    string aType;
    string super;
    string seq;
    string price;
    Server * server= new Server();
    srand(time(NULL));
    cout << "Enter the type of Auction" << endl;
    cin >> aType;

    cout << "Is this a Super auction?" << endl;
    cin >> super;
    if(super == "yes"){
        server->isSuper = true;
    }else{
        server->isSuper = false;
    }

    cout << "Is this a Sequential?" << endl;
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

