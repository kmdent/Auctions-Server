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
            (*agents.at(i)).bid(askPrice);

        }
    }
}

void Server::runDescending(){

    bool isOver = false;

    for(int i = 0; i < numAgents; i++){
        agents.push_back(new dAgent(i));
    }

    while(!isOver){
        for(int i = 0; i < agents.size(); i++){

        }
    }
}

void Server::runSealedPrice(){

    bool isOver = false;

    for(int i = 0; i < numAgents; i++){
        agents.push_back(new sAgent(i));
    }

    while(!isOver){
        for(int i = 0; i < agents.size(); i++){

        }
    }


}

int main(int argc, char *argv[]){


    string aType;
    string super;
    string seq;
    Server * server= new Server();
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

    if(!aType.compare("Ascending")){
        cout << "running ascening" << endl;
        server->runAscending();
    }else if(!aType.compare("Decending")){
        server->runDescending();
    }else if(!aType.compare("Sealed")){
        server->runSealedPrice();
    }

    delete server;
    return 1;

}

