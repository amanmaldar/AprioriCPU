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
using namespace std;


int numItems=0;
int numTransactions=1;
int maxItemsetSize=0;
int minSupp = 0.07;

double minSupport;
double minConfidence;
int number_of_strong_rules=0;

vector<set<int>> transactions;


clock_t t1,t2;

string fileName;
string programName;
string displayOption="?";


void initialize();


int main(int argc, char **argv){

    programName = "main";
    //fileName = "D:\\Github Programs\\Apriori\\test3.txt";
    fileName = "test3.txt";
    //minSupp = 0.07;
    minConfidence = 0.8;
    displayOption = 'a';

    t1=clock();

    initialize();
    return 1;



    t2=clock();
    double diff=((double)t2-(double)t1);
    double seconds = diff / CLOCKS_PER_SEC;

    cout<<"Execution time: ";
    cout<<round(seconds);
    cout<<" seconds"<<endl;

    return 0;
}

void initialize(){

    ifstream infile(fileName);
    string line;
    //map <int,int> item_count;
    vector <int> item_count;
    for (int i = 0; i <= 1000; ++i){
        item_count.push_back(0) ;
    }
    vector <vector <int>> itemToTID;    //each vector relates to single TID
    //each vector keeps track of the transactions number in which particular TID is present
    // used later to calculate the count of pair

  vector <int> tmp;
    tmp.push_back(0);
    for (int i = 1; i <= 1000; ++i){
        itemToTID.push_back(tmp) ;
    }



    int n;
    int m;

    while (getline(infile,line)){
         istringstream iss(line);    //iss refers to each element in line
        //std::cout << "lines are: " << line << std::endl;
        m=0;

        while( iss >> n ){      // work on a every entry in sible line


            item_count[n] +=1;
            // m captures the number of items in one transaction (one line of file).
            m +=1;

            itemToTID.at(n).push_back(numTransactions);
            // these vectors would be automatically sorted and hence we can use set_intersection later.

        }

        // find maximum number of items in one transaction.
        if (m > maxItemsetSize){
            maxItemsetSize=m;
        }

        numTransactions +=1;
    }

    numTransactions -=1; //originally initalized with 1 to push at location 1 in vectors
    //cout << "kjsghdfkjsd" << numTransactions << endl;
    /*
    for(int i=0;i<1000;i++)
    {
        if (item_count.at(i) != 0) {
            cout << "element count: " << i << " : " << item_count[i] << endl;
        }
    }*/

/*
    for (int i = 0 ;i < 1000; i ++)
    {
        //cout << "checking size: " << itemToTID.at(i).size() << endl;
        if (itemToTID[i].size() != 1) {
            cout << "item tid: " << i << " is present in : ";
            for(int j=1; j < itemToTID[i].size();j++)
                 cout << itemToTID[i].at(j) << " " ;

            cout << endl;
        }

    }*/
    // WE ARE DONE WITH PARSING FILE ***************works fine till here
    //return ;

    // Following code generates single items which have support greater than min_sup
    // compare the occurance of the object against min support
    minSupport=round(minSupp * numTransactions);

    vector <int> onefrequentItemSet;
    onefrequentItemSet.push_back(0);
    for (int i=1; i<= 1000; i++)
    {
        if(item_count[i] >= minSupport){
           cout  << "minSupport" << minSupport << endl;
            // cout << "item id is: " << i << " item_count is: " << item_count[i] << endl;
            onefrequentItemSet.push_back(i);     //push TID into frequentItem
        }

    }

    cout << "size of frequent items is: " << onefrequentItemSet.size() -1 << endl;
    cout << "qualified items are: ";


    for (int i=1; i<= onefrequentItemSet.size() -1; i++)
    {
        cout << onefrequentItemSet[i] << " ";
    }
    cout << endl;

    return;
    // make a pair of frequest items

    typedef struct{
        //sets are indexed with 0. So we use iterator starting from (begin)
        set <pair <int,int> > setofPairOfTwo;
        set <pair <int,int> > filteredSetofPairOfTwo;
        //map <set <pair <int,int> > ,int > mapofPairOfTwo;

    }Struct_pairOfTwo;
    Struct_pairOfTwo struct_pairOfTwo;

    //set <pair <int,int> >pairOfTwo;
    pair <int,int>  tmpPair;
    for (int i=1;i <= onefrequentItemSet.size() -1 -1;i++)
    {
        for (int j=i+1;j <= onefrequentItemSet.size() -1;j++){

            //tmpPair.first = onefrequentItemSet[i];
           // tmpPair.second = onefrequentItemSet[j];
            //struct_pairOfTwo.mapofPairOfTwo.insert(make_pair(tmpPair,1));

            struct_pairOfTwo.setofPairOfTwo.insert(make_pair(onefrequentItemSet[i],onefrequentItemSet[j]));
            //make_pair(set<int,int> (frequentItems.at(i),frequentItems.at(j)));
        }
    }

    cout << "printing pairs: " << endl;
    //map <pair <int,int>, int> pairCount;



    set <pair <int,int> > :: iterator it;
    for(it = struct_pairOfTwo.setofPairOfTwo.begin(); it != struct_pairOfTwo.setofPairOfTwo.end(); it++)
    {
        int fir = it->first;
        int sec = it->second;
        cout << "Pair is: (" <<it->first << "," << it->second << ") " ;
        // itemToTID.at(it->first); this is vector 1
        // itemToTID.at(it->second); this is vector 2
        vector <int> vec2;
        // read corresponding itemToTID vector and find out common elements from them
        // this is compared against min_sup later
        std::set_intersection(  itemToTID.at(it->first).begin()+1, itemToTID.at(it->first).end(),
                                itemToTID.at(it->second).begin()+1, itemToTID.at(it->second).end(),
                                std::back_inserter( vec2 )  );
        cout << " Frequency: " << vec2.size() ;;
        cout << " Common TIDs: " ;
        for (int i=0;i<vec2.size();i++)        {            cout << vec2[i] << " " ;        }
        //pairCount.insert(make_pair(it->first,it->second),vec2.size());
        cout << endl;



        // now create a new set having only the pair which has grater support
        if (vec2.size() >= minSupp){     //for 5 transactions minSupp is 2 . MinSupp is 0.4 by default
            //  struct_pairOfTwo.setofPairOfTwo.insert(make_pair(onefrequentItemSet[i],onefrequentItemSet[j]));
            //cout << "inserting into new set" << endl;
            struct_pairOfTwo.filteredSetofPairOfTwo.insert(make_pair(fir,sec));
        }
        vec2.clear();
    }

    set <pair <int,int> > :: iterator it1;
    cout << "filtered pair of 2 with bigger support is: " << endl;
    for(it1 = struct_pairOfTwo.filteredSetofPairOfTwo.begin(); it1 != struct_pairOfTwo.filteredSetofPairOfTwo.end(); it1++){
        cout << "Filtered Pair is : (" << it1->first << "," << it1->second << ")" << endl;
    }


    /*cout << "numTransactions is: " << numTransactions << endl;
    cout << "support is: " << minSupp << endl; */
    // now

    //  First k - 2 = 2 items must match in pass k = 4
// k is size of new itemeset to be generated. Here k =3
    //make a pair of 3 now
    int delta=1,a;

    set <pair <int,int> > myset = struct_pairOfTwo.filteredSetofPairOfTwo;
    for (it = myset.begin(); it != myset.end(); it++,delta++ ) {
        //cout << "parent pair is : " << it->first << " "<< it->second  << endl;
        a = it->first;

        it1 = myset.begin();                     // assign second iterator to same set
        for (int k = 0; k < delta; k++) { it1++; }   //add a offset to second iterator and iterate over same set

        vector <int> vec2, vec3;
        for (it1 = it1; it1 != myset.end(); it1++) {  //iterating over same set.
            if (a == it1->first) {
                // find out the occurances for the particular pair using set_oteration

                std::set_intersection(itemToTID.at(it->first).begin() + 1, itemToTID.at(it->first).end(),
                                      itemToTID.at(it->second).begin() + 1, itemToTID.at(it->second).end(),
                                       std::back_inserter(vec2));

                std::set_intersection(vec2.begin(), vec2.end(),
                                      itemToTID.at(it1->second).begin() + 1, itemToTID.at(it1->second).end(),
                                      std::back_inserter(vec3));

                //if (1) {
                if (vec3.size() >= minSupp) {
                    cout << "pair is : " << it->first << " " << it->second << " " << it1->second;
                    cout << " Frequency: " << vec3.size();;
                    cout << " Common TIDs: ";
                    for (int i = 0; i < vec3.size(); i++) { cout << vec3[i] << " "; }
                    cout << endl;
                }
                //pairCount.insert(make_pair(it->first,it->second),vec2.size());

                vec2.clear();
                vec3.clear();

            }

        }
    }



    infile.close();

    return;
}




