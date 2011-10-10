#include "server.h"
#include "string"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){


    string aType;
    string super;
    string seq;
    Server * server= new Server();
    cout << "Enter the type of Auction" << endl;
    //cin >> aType;

    cout << "Is this a Super auction?" << endl;
    //cin >> super;
    if(super == "yes"){
        server->isSuper = true;
    }else{
        server->isSuper = false;
    }

    cout << "Is this a Sequential?" << endl;
    //cin >> seq;
    if(seq == "yes"){
        server->isSequential = true;
    }else{
        server->isSequential = false;
    }

    cout << "Enter the number of Bidders" << endl;
    //cin >> server->numAgents;

    if(aType == "Ascening"){
        server->runAscending();
    }else if(aType == "Decending"){
        server->runDescending();
    }else if(aType == "Sealed"){
        server->runSealedPrice();
    }

    delete server;
    return 1;

}
