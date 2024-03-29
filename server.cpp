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
#include <cmath>


using namespace std;

/*GLOBALS*/
vector<vector<int> * > * subsets;
vector<bool> bTypes;



Server::Server()
{
}

Server::~Server()
{
}

float Server::runAscending(){
    bool isOver = false;
    vector<vector<float> > bids;
    vector<int> winners;
    vector<float> secondPrices;
    vector<float> highestBids;
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
        a->MV = bTypes.at(i);
        a->createValuations(subsets, numGoods);
        a->numBidders = numAgents;
        a->firstPrice = firstPrice;
        agents.push_back(a);
    }
    if(! isSequential){
        while(! isOver){
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

                winningPrices.at(good) = secondPrices.at(good);
                askPrices.at(good) = highestBids.at(good)+.05;

            }

           // cout << "\n Second prices:  ";
           // for(int k =0; k < secondPrices.size(); k++){
           //     cout << "Good " <<k << ": " << secondPrices.at(k) << ", ";
           // }
           // cout << endl;

            // Round is over

            isOver = true;
            for(int i = 0; i< numGoods; i++){
                if(quiescent.at(i) == 0){
                    isOver = false;
                    break;
                }
            }

           /* for(int i = 0; i < numGoods; i++){
                cout <<"Good: " << i << endl;
                for(int j = 0; j < numAgents; j++){
                    cout << "Bidder: "<< j << " Bid: " << bids.at(j).at(i) << endl;
                }
                cout <<"Winner: " <<  winners.at(i) << " with a bid of: " << highestBids.at(i) << endl;
                cout << "new round ask price: " << askPrices.at(i) << endl;
            }
            string a;
            cout << "Press any character and hit enter to start next round"  << endl;
            //cin >> a; */
        }
    }

   //cout << "-------------------------Auction Results__________________________"<<endl;
    for(int good = 0; good < numGoods; good++){
     //   cout << "Good " << good << endl;
        for(int i = 0; i < numGoods; i++){

            if(winners.at(i) == -1){
                winners.at(i) = (int)(((float)rand() / (float)(RAND_MAX))*numAgents);
       //         cout << "No one bid. We gave it to: " << winners.at(i)<< "+++++++++++++++++++++++++++++uaeoueoaueoa+++++++++++++++++++++++++++++++++" << endl;
            }
            agents.at(winners.at(i))->payments.at(i) = secondPrices.at(i);

        }
       // for(int i = 0; i < numAgents; i++){
        //    cout <<"Bidder " << i << "{ "<< "Value: " << agents.at(i)->valuations.at(good) << ", Bid: " << bids.at(i).at(good) << ", Paid: "<< agents.at(i)->payments.at(good) <<  "}"<<endl;
       // }
    }


    for(int i =0; i < winners.size(); i++){
        agents.at(winners.at(i))->goodsWon.push_back(i+1);
    }

  //  cout << "\n Second prices:  ";
    //for(int k =0; k < secondPrices.size(); k++){
    //    cout << "Good " <<k << ": " << secondPrices.at(k) << ", ";
    //}
    //cout << endl;



   /* cout << "------------------------Agent information-------------------------" << endl;
    for (int i = 0; i < agents.size(); ++i) {
        aAgent * tmpAgent = (aAgent *)agents.at(i);
        cout << "---------------Agent " << i <<  "---------------" <<  endl;
        cout << "Valuations: ";
        for(int j = 0; j< tmpAgent->valuations.size(); j++){
            cout << tmpAgent->valuations.at(j) << " ";
        }
        cout << ",Lambda: " << tmpAgent->lambda << "Surplus: " << tmpAgent->surplus(&(tmpAgent->goodsWon),secondPrices) << endl;

    }*/

    float toReturn = agents.at(0)->surplus(&(agents.at(0)->goodsWon),secondPrices);

    for(int i = 0; i < agents.size(); i++){
        delete (aAgent *) agents.at(i);
    }
    agents.clear();
    return toReturn;

}

float Server::runSealedPrice(){

    vector<vector<float> > bids;
    vector<int> winners;
    vector<float> highestBids;
    vector<float> secondPrices;

    for(int i = 0; i < numGoods; i++){
        winners.push_back(-1);
    }
    for(int i = 0; i < numAgents; i++){
        sAgent *s = new sAgent(i);
        s->MV = bTypes.at(i);
        s->createValuations(subsets,numGoods);
        s->numBidders = numAgents;
        s->firstPrice = firstPrice;
        agents.push_back(s);
    }

    if(! isSequential){ //simultaneous
        for(int i = 0; i < agents.size(); i++){
            vector<float> predictions;
            //bids.push_back(((sAgent*)(agents.at(i)))->bidSimultaneous(numGoods, predictions, 0));
            bids.push_back(((sAgent*)(agents.at(i)))->bidSimultaneous(numGoods, (vector<float>)NULL, 1));
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
            agents.at(winners.at(good))->goodsWon.push_back(good +1); /*Sets up the goods won array*/
        }

        //Auction is done

    }





    cout << "-------------------------Auction Results__________________________"<<endl;
    for(int good = 0; good < numGoods; good++){
        cout << "Good " << good << endl;
        for(int i = 0; i < numGoods; i++){
            agents.at(winners.at(i))->payments.at(i) = secondPrices.at(i);
        }
        for(int i = 0; i < numAgents; i++){
            cout <<"Bidder " << i << "{ "<< " Bid: " << bids.at(i).at(good) << ", Paid: "<< agents.at(i)->payments.at(good) << "}"<<endl;
        }
        cout <<"Winner of that round: "<<  winners.at(good) << endl;
    }

    cout << "------------------------Agent information-------------------------" << endl;
    string dummy;
    for (int i = 0; i < agents.size(); ++i) {
        sAgent * tmpAgent = (sAgent *)agents.at(i);
        cout << "---------------Agent " << i <<  "---------------" <<  endl;
        cout << "Valuations: ";
        for(int j = 0; j< tmpAgent->valuations.size(); j++){
            cout << tmpAgent->valuations.at(j) << " ";
        }
        cout << endl;
        cout << "Lambda: " << tmpAgent->lambda << " Is MV: " << tmpAgent->MV <<  endl;
        for (int j = 0; j < tmpAgent->bundleVal.size(); ++j) {
            cout << "Subset: ";
            for(int l = 0; l< subsets->at(j)->size(); l++){
                cout << subsets->at(j)->at(l) << ", ";
            }
            cout <<" Value: "<< tmpAgent->bundleVal.at(j) << endl;
        }
        cout<< "Surplus: " << tmpAgent->surplus(&(tmpAgent->goodsWon),secondPrices) << endl;


    }
    sAgent *firstAgent = (sAgent*)agents.at(0);
    float surplus = firstAgent->surplus(&(firstAgent->goodsWon), secondPrices);
    for(int i =0; i < agents.size(); i++){
        sAgent *tmp =(sAgent *) agents.at(i);
        delete tmp;
    }
    agents.clear();
    return surplus;

}

vector<vector<int> * > * Asub(vector<vector<int> * > * subsets, int s[],int p,int k,int t[],int q=0,int r=0){
    if(q==k){
        vector<int> * tmp = new vector<int>();
        for(int i=0;i<k;i++){
            tmp->push_back(t[i]);
        }
        subsets->push_back(tmp);
    }else{
        for(int i=r;i<p;i++){
            t[q]=s[i];
            Asub(subsets, s,p,k,t,q+1,i+1);
        }
    }
}

int main(int argc, char *argv[]){

    /*Generates all of the subsets for the aquisition problem*/
    subsets = new vector<vector<int> * >();
    subsets->push_back(new vector<int>());
    int s[]={1,2,3,4,5},t[5];
    for(int i = 1; i <=5; i++){
        Asub(subsets, s,5,i,t);
    }




    string aType;
    Server * server= new Server();
    srand(time(NULL));
    rand();

    server->firstPrice = false;
    server->numGoods = 5;
    server->isSequential = false;
    server->numAgents = 8;

    int num_iterations = 10000;

    for(int i = 0; i < server->numAgents; i++){
        if(i == 0){
            bTypes.push_back(false);
        }else{
            bTypes.push_back(true);
        }
    }


    // Getting the auction type
    cout << "Enter the type of Auction" << endl;
    cin >> aType;

    float totalSurplus = 0.0;
    float averageSurplus = 0.0;

    if(!aType.compare("Ascending") || !aType.compare("A")){
        cout << "running ascending" << endl;

        for(int i = 0; i < num_iterations; i++){
           totalSurplus += server->runAscending();
           if(fmod((double)i,(double)100) == 0){
               cout << "Iteration: " << i <<endl;
           }
        }
        averageSurplus = totalSurplus/num_iterations;
        cout << "average Surplus: " <<averageSurplus << endl;
    }else{
        vector<float> surplus;
        float totalSurplus = 0;
        for(int i = 0; i<num_iterations; i++){
            cout << "running sealed price" << endl;
            float s = server->runSealedPrice();
            cout << "Agent 1's surplus: " << s << endl;
            totalSurplus += s;
        }
        cout << "average surplus: " << totalSurplus/num_iterations << endl;
    }


    delete server;
    return 1;




}

