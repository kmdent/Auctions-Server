#include "sagent.h"
#include "iostream"
#include "price_predictor.h"
#define LAMDBA_THRESHOLD 3

sAgent::sAgent(int id) : Agent(id)
{
}

sAgent::~sAgent(){

}

vector<float> sAgent::bidSimultaneous(int numGoods, vector<float> prediction,bool isPrediction){
    vector<float> v;

    if(MV){
        vector<float> tmpPrice;
        tmpPrice.push_back(20);
        tmpPrice.push_back(20);
        tmpPrice.push_back(20);
        tmpPrice.push_back(20);
        tmpPrice.push_back(20);




        if(isPrediction == 1){
            string dummy;
            price_predictor * p = new price_predictor(tmpPrice,0, subsets);
            prediction = p->getPrices();
            cout << "Prediction ended &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
            cin >> dummy;
        }
        else{
            prediction.clear();
            prediction.push_back(15.75);
            prediction.push_back(11.3);
            prediction.push_back(7.6);
            prediction.push_back(3.5);
            prediction.push_back(.55);
        }


//        cout << "/=======================================" << endl;
//        cout << "Price Vec In the bid function: ";
//        for(int i = 0; i< prediction.size(); i++){
//            cout << prediction.at(i) << " ";
//        }
//        cout << endl;
//        cout << "Num goods " << numGoods << endl;
//        cout << "/=======================================" << endl;

        for(int i = 0; i < numGoods; i++){
            float tmpbid = marginalValue(i+1,prediction);
            v.push_back(tmpbid);
        }
    }else{
        cout << "playing modified strategy" << endl;
        vector<float> tmpPrice;
        tmpPrice.push_back(14);
        tmpPrice.push_back(12);
        tmpPrice.push_back(10);
        tmpPrice.push_back(8);
        tmpPrice.push_back(6);
        if(isPrediction == 1){
            string dummy;
            price_predictor * p = new price_predictor(tmpPrice,0, subsets);
            prediction = p->getPrices();
            cout << "Prediction ended &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
            cin >> dummy;
        }
        else{
            prediction.clear();
            prediction.push_back(15.75);
            prediction.push_back(11.3);
            prediction.push_back(7.6);
            prediction.push_back(3.5);
            prediction.push_back(.56);
        }
//        cout << "/=======================================" << endl;
//        cout << "Price Vec In the bid function: ";
//        for(int i = 0; i< prediction.size(); i++){
//            cout << prediction.at(i) << " ";
//        }
//        cout << endl;
//        cout << "Num goods " << numGoods << endl;
//        cout << "/=======================================" << endl;

        for(int i = 0; i < numGoods; i++){
            if(lambda < LAMDBA_THRESHOLD){
                float tmpbid = marginalValue(i+1,prediction);
                v.push_back(tmpbid);
            }
            else v.push_back(0);
        }
    }
    return v;
}

