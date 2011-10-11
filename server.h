#ifndef SERVER_H
#define SERVER_H

#include "agent.h"
#include "vector"
class Server
{
public:
    int numAgents;
    bool isSuper;
    bool isSequential;
    int highBidder;
    vector<Agent*> agents;

    Server();
    virtual ~Server();
    void runAscending();
    void runDescending();
    void runSealedPrice();

};

#endif // SERVER_H
