#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <iomanip>
#include <typeinfo>
#include "chrono"
using namespace std;


int TID_Transactions = 0;
int maxItemsetSize=0;
double minSupp = 0.001; // 0.001;

double minSupport;
double minConfidence;
int number_of_strong_rules=0;

int one_freq_itemset=0;
int two_freq_itemset=0;
int three_freq_itemset=0;
int four_freq_itemset=0;

int maxItemID = 1000;

string fileName;

void initialize();


int main(int argc, char **argv){

    if (argc > 1)
    {
        fileName = "test3.txt";
    }
    else{
        fileName = "D:\\Github Programs\\Apriori\\test3.txt";
    }




    auto start = std::chrono::high_resolution_clock::now();

    initialize();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> el = end - start;
    cout<<"Execution time New: " << el.count() * 1000 << " mS " << endl;

    return 0;
}

void initialize(){

    ifstream infile(fileName);
    string line;

    // itemIDcount is used to store number of times particular itemID appears in dataset.
    // It is used to determine support for single elements.
    // itemID will go from 1 to 1000
    vector <int> itemIDcount;
    for (int i = 1; i <= maxItemID; ++i){
        itemIDcount.push_back(0) ;          //initialize all the itemID (1 -> 1000) counts with zero.
        //itemIDcount[i] = 0;
    }

    // A single vector is associated with every itemID.
    // That vector stores the TID [Transaction ID] in which particular itemID appears.
    vector <vector <int>> itemId_TidMapping;
    // used later to calculate the count of pair

    vector <int> tmpTID;
    tmpTID.push_back(0);
    for (int i = 1; i <= maxItemID; ++i){
        //initialize each vector element in itemId_TidMapping with a vector tmpTID
        itemId_TidMapping.push_back(tmpTID) ;
    }


    int n;

    while (getline(infile,line)){
         istringstream iss(line);       //iss refers to each element in line
        //cout << "Transactions are: " << line << endl;
        TID_Transactions +=1;

        while( iss >> n ){              // work on a every single itemID on transaction.

            itemIDcount[n] +=1;
            // m captures the number of items in one transaction (one line of file).

            //push TID to corresponding vector of itemID
            itemId_TidMapping.at(n).push_back(TID_Transactions);
            // these vectors would be automatically sorted and hence we can use set_intersection later.
        }
    }
    // WE ARE DONE WITH PARSING FILE ***************works fine till here
    //return ;

    // Following code generates single items which have support greater than min_sup
    // compare the occurrence of the object against minSupport

    //cout << "Test1: " << minSupport << " " << TID_Transactions << " " << minSupp << endl;

    vector <int> onefrequentItemSet;
    onefrequentItemSet.push_back(0);    // initialized first index with 0 as we are not using it.

    minSupport = round(minSupp *  TID_Transactions);

    for (int i=1; i<= maxItemID; i++)
    {
        if(itemIDcount[i] >= minSupport){
         //cout << "item id is: " << i << " item_count is: " << itemIDcount[i] << endl;
            onefrequentItemSet.push_back(i);     //push TID into frequentItem
            one_freq_itemset++;
        }
    }

    cout << "one_freq_itemset: " << one_freq_itemset << endl;

    // make a pair of frequent items

    set <pair <int,int> > setofPairOfTwo;
    set <pair <int,int> > filteredSetofPairOfTwo;

    //set <pair <int,int> >pairOfTwo;
    pair <int,int>  tmpPair;
    for (int i=1;i <= onefrequentItemSet.size() -1 -1; i++)     //-1 is done for eliminating first entry
    {
        for (int j=i+1;j <= onefrequentItemSet.size() -1; j++){

            setofPairOfTwo.insert(make_pair(onefrequentItemSet[i],onefrequentItemSet[j]));
        }
    }


    // cout << "printing pairs: " << endl;

    set <pair <int,int> > :: iterator it;
    for(it = setofPairOfTwo.begin(); it != setofPairOfTwo.end(); it++)
    {
        int fir = it->first;
        int sec = it->second;
         //cout << "Pair is: (" <<it->first << "," << it->second << ") " << endl;
        // itemToTID.at(it->first); this is vector 1
        // itemToTID.at(it->second); this is vector 2
        vector <int> vec2;
        // read corresponding itemToTID vector and find out common elements from them
        // this is compared against min_sup later
        std::set_intersection(  itemId_TidMapping.at(it->first).begin()+1, itemId_TidMapping.at(it->first).end(),
                                itemId_TidMapping.at(it->second).begin()+1, itemId_TidMapping.at(it->second).end(),
                                std::back_inserter( vec2 )  );

        // now create a new set having only the pair which has grater support
        if (vec2.size() >= minSupport){     //for 5 transactions minSupp is 2 . MinSupp is 0.4 by default
            filteredSetofPairOfTwo.insert(make_pair(fir,sec));
            two_freq_itemset++;
        }
        vec2.clear();
    }
    cout << "two_freq_itemset: " << two_freq_itemset << endl;

    //return;
    /*
    set <pair <int,int> > :: iterator it1;
    cout << "filtered pair of 2 with bigger support is: " << endl;
    for(it1 = struct_pairOfTwo.filteredSetofPairOfTwo.begin(); it1 != struct_pairOfTwo.filteredSetofPairOfTwo.end(); it1++){
        cout << "Filtered Pair is : (" << it1->first << "," << it1->second << ")" << endl;
    }*/

    // works fine till here **********

   // return;


    //make a pair of 3 now
    int delta=1,a1;

    typedef struct {
        //int a=0,b=0,c=0;
        int a;
        int b;
        int c;
    } SetofPairOfThree;
    SetofPairOfThree tmpSet;

    //SetofPairOfThree tmp1;
    vector <SetofPairOfThree>  vectorofPairOfThree;
  /*  for (int i=1;i<=1000;i++){
        //vectorofPairOfThree.push_back(tmp1);
    }*/

    set <pair <int,int> > myset = filteredSetofPairOfTwo;
    set <pair <int,int> > :: iterator it1;

    // FOLLOWING 2 FOR LOOPS GENERATE SET OF 3 ITEMS
    //int delta1= 1;
    for (it = myset.begin(); it != myset.end(); it++,delta++ ) {
        //cout << "parent pair is : " << it->first << " "<< it->second  << endl;
        a1 = it->first;

        it1 = myset.begin();                     // assign second iterator to same set *imp
        for (int k = 0; k < delta; k++) { it1++; }   //add a offset to second iterator and iterate over same set

        vector <int> vec2, vec3;
        for (it1 = it1; it1 != myset.end(); it1++) {  //iterating over same set.
            if (a1 == it1->first) {
                // find out the occurrences for the particular pair using set_operation

                std::set_intersection(itemId_TidMapping.at(it->first).begin() + 1, itemId_TidMapping.at(it->first).end(),
                                      itemId_TidMapping.at(it->second).begin() + 1, itemId_TidMapping.at(it->second).end(),
                                       std::back_inserter(vec2));

                std::set_intersection(vec2.begin(), vec2.end(),
                                      itemId_TidMapping.at(it1->second).begin() + 1, itemId_TidMapping.at(it1->second).end(),
                                      std::back_inserter(vec3));

                //SetofPairOfThree tmpSet;
               // tmpSet.a= 0; tmpSet.b=0; tmpSet.c=0;
                //cout << "testing min sup 2" << minSupport << endl;

                if (vec3.size() >= minSupport) {
                    three_freq_itemset++;
                    tmpSet.a = it->first;
                    tmpSet.b = it ->second;
                    tmpSet.c = it1->second;
                    vectorofPairOfThree.push_back(tmpSet);

                    //cout << "pair is : " << it->first << " " << it->second << " " << it1->second << endl;
                /*    cout << " Frequency: " << vec3.size();;
                    cout << " Common TIDs: "; */

                    // need to save three pairs yet
                }

                vec2.clear();  vec3.clear();
            }
        }

    }
    cout << "three_freq_itemset: " << three_freq_itemset << endl;

    //return;
    vector <SetofPairOfThree> :: iterator it2,it3;

    int c,d;
    int delta1= 1;

    for(it2 = vectorofPairOfThree.begin(); it2 != vectorofPairOfThree.end(); it2++,delta1++)
    {
        it3 = vectorofPairOfThree.begin();                     // assign second iterator to same set *imp
        for (int k = 0; k < delta1; k++) { it3++; }   //add a offset to second iterator and iterate over same set

        c = it2.base()->a;
        d = it2.base()->b;
       // cout << "parent pair is : " << c << " "<< d  << endl;

        vector <int> vec4, vec5;
        for (it3 = it3; it3 != vectorofPairOfThree.end(); it3++) {  //iterating over same set.

           // cout << "pair are : " << it2.base()->a << " "<< it2.base()->b  << " " << it2.base()->c <<" " <<
             //    it3.base()->a << " "<< it3.base()->b  << " " << it3.base()->c << endl;

            if (c == it3.base()->a && d == it3.base()->b) {
                // find out the occurrences for the particular pair using set_operation
                //cout << "filtered pair are : " << it2.base()->a << " "<< it2.base()->b  << " " << it2.base()->c <<" " << it3.base()->c << endl;

                std::set_intersection(itemId_TidMapping.at(it2.base()->a).begin() + 1, itemId_TidMapping.at(it2.base()->a).end(),
                                      itemId_TidMapping.at(it2.base()->c).begin() + 1, itemId_TidMapping.at(it2.base()->c).end(),
                                      std::back_inserter(vec4));

                std::set_intersection(vec4.begin(), vec4.end(),
                                      itemId_TidMapping.at(it3.base()->c).begin() + 1, itemId_TidMapping.at(it3.base()->c).end(),
                                      std::back_inserter(vec5));

                if (vec5.size() >= minSupport) {
                    vec4.clear(); vec5.clear();

                    std::set_intersection(itemId_TidMapping.at(it3.base()->b).begin() + 1, itemId_TidMapping.at(it3.base()->b).end(),
                                          itemId_TidMapping.at(it2.base()->c).begin() + 1, itemId_TidMapping.at(it2.base()->c).end(),
                                          std::back_inserter(vec4));

                    std::set_intersection(vec4.begin(), vec4.end(),
                                          itemId_TidMapping.at(it3.base()->c).begin() + 1, itemId_TidMapping.at(it3.base()->c).end(),
                                          std::back_inserter(vec5));
                        if (vec5.size() >= minSupport) {
                           // cout << "filtered pair are : " << it2.base()->a << " "<< it2.base()->b  << " " << it2.base()->c <<" " << it3.base()->c << endl;
                            four_freq_itemset++;
                        }
                }


            }
        }


    }
    cout << "four_freq_itemset: " << four_freq_itemset << endl;

    infile.close();

    return;
}




