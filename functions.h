//
// Created by Lenovo on 3/26/2018.
//

#ifndef APRIORI_FUNCTIONS_H
#define APRIORI_FUNCTIONS_H
#include "apriori.hcu"


void parse_database(){

    fileName = "6entries.txt"; 


    ifstream infile(fileName);
    string line;
    // parse_database();
    for (int i = 0; i <= maxItemID; ++i){
        itemIDcount.push_back(0) ;          //initialize all the itemID (1 -> 1000) counts with zero.
    }

    // used later to calculate the count of pair

    vector <int> tmpTID;
    tmpTID.push_back(0);
    for (int i = 0; i <= maxItemID; i++){
        //initialize each vector element in itemId_TidMapping with a vector tmpTID
        itemId_TidMapping.push_back(tmpTID) ;
        //itemIDcount[i] = 0;
    }

    int n;
    TID_Transactions = 1;

    while (getline(infile,line)){
        istringstream iss(line);       //iss refers to each element in line
        //cout << "Transactions are: " << line << endl;
        //TID_Transactions +=1;

        while( iss >> n ){              // work on a every single itemID on transaction.

            itemIDcount[n] +=1;
            totalItems++;
            // m captures the number of items in one transaction (one line of file).

            //push TID to corresponding vector of itemID
            itemId_TidMapping.at(n).push_back(TID_Transactions);
            // these vectors would be automatically sorted and hence we can use set_intersection later.
        }
        TID_Transactions++;
    } // Parsing done
    cout << "totalItems: " << totalItems << endl;
    totalItems += maxItemID + 1;    //used to adjust lenght of A
    infile.close();

}

#endif //APRIORI_FUNCTIONS_H
