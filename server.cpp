#include "server.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "stdio.h"
#include "vector"
#include "agent.h"
#include "aagent.h"
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
        a->createValuations(numGoods);
        a->numBidders = numAgents;
        a->firstPrice = firstPrice;
        agents.push_back(a);
    }
    if(! isSequential){
        while(! isOver){
            cout << "Starting round"  << endl;
            bids.clear();
            for(int i = 0; i < agents.size(); i++){
                bids.push_back(((aAgent*)(agents.at(i)))->bidSimultaneous(numGoods, winners, winningPrices, askPrices));
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

            for(int i = 0; i < numGoods; i++){
                cout <<"Good: " << i << endl;
                for(int j = 0; j < numAgents; j++){
                    cout << "Bidder: "<< j << " Bid: " << bids.at(j).at(i) << endl;
                }
                cout <<"Winner: " <<  winners.at(i) << " with a bid of: " << highestBids.at(i) << endl;
                cout << "new round ask price: " << askPrices.at(i) << endl;
            }
            string a;
            cout << "Press any character and hit enter to start next round"  << endl;
            cin >> a;
        }
    }
    cout << "-------------------------Auction Results__________________________"<<endl;
    for(int good = 0; good < numGoods; good++){
        cout << "Good " << good << endl;
        for(int i = 0; i < numGoods; i++){
            if(firstPrice){
                agents.at(winners.at(i))->payments.at(i) = highestBids.at(i);
            }
            else agents.at(winners.at(i))->payments.at(i) = secondPrices.at(i);
        }
        for(int i = 0; i < numAgents; i++){
            cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuations.at(good) << ", Bid: " << bids.at(i).at(good) << ", Paid: "<< agents.at(i)->payments.at(good) <<  "}"<<endl;
        }
    }

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
            highestBids.push_back(highBid);
            secondPrices.push_back(secondBid);
        }

        //Auction is done

    }

    cout << "-------------------------Auction Results__________________________"<<endl;
    for(int good = 0; good < numGoods; good++){
        cout << "Good " << good << endl;
        for(int i = 0; i < numGoods; i++){
            if(firstPrice){
                agents.at(winners.at(i))->payments.at(i) = highestBids.at(i);
            }
            else agents.at(winners.at(i))->payments.at(i) = secondPrices.at(i);
        }
        for(int i = 0; i < numAgents; i++){
            cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuations.at(good) << ", Bid: " << bids.at(i).at(good) << ", Paid: "<< agents.at(i)->payments.at(good) << "}"<<endl;
        }
    }
}

int main(int argc, char *argv[]){

    string aType;
    Server * server= new Server();
    srand(time(NULL));
    rand();

    server->firstPrice = false;
    server->numGoods = 5;
    server->isSequential = false;
    server->numAgents = 8;


    // Getting the auction type
    cout << "Enter the type of Auction" << endl;
    cin >> aType;

    if(!aType.compare("Ascending") || !aType.compare("A")){
        cout << "running ascending" << endl;
        server->runAscending();
    }else{
        cout << "running sealed price" << endl;
        server->runSealedPrice();
    }

    delete server;
    return 1;

}

