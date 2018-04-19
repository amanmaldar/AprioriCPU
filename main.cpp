/************************************************************************
Author - Aman Maldar
Simple code - parallel version of data association.
Static value of minSupport=1. This will show all the pairs generated.
File = 6entries.txt
Limitation - Generates only till set of 4 pairs as of now.
It needs multiple changes for the data structure as well. Need to reconfigure it.

*************************************************************************/
#include "apriori.h"
#include "functions.h"


double minSupp = 0.001; // 0.001;

void Execute(int argc){

    parse_database(argc);

    L1.push_back(0);    // initialized first index with 0 as we are not using it.
    //minSupport = round(minSupp *  TID_Transactions);
    minSupport = 1;
    // Following code generates single items which have support greater than min_sup
    // compare the occurrence of the object against minSupport

    cout << "Support:" << minSupport << endl;
    //Generate L1 - filtered single items ? I think this should be C1, not L1.

    for (int i=1; i<= maxItemID; i++)
    {
        if(itemIDcount[i] >= minSupport){
            L1.push_back(i);     //push TID into frequentItem
            one_freq_itemset++;
            cout << "1 Frequent Item is: (" << i << ") Freq is: " << itemIDcount[i] << endl;
        }
    }
    cout << "one_freq_itemset:      " << one_freq_itemset << endl;
    //******************************************************************************************************************
    //Generate L2 .  Make a pair of frequent items in L1
    for (int i=1;i <= L1.size() -1 -1; i++)     //-1 is done for eliminating first entry
    {
        for (int j=i+1;j <= L1.size() -1; j++){
            twoStruct.a = L1[i];
            twoStruct.b = L1[j];
            L2.push_back(twoStruct);
        }
    }
    //******************************************************************************************************************
    //Generate C2. Prune L2 . Compare against min_support and remove less frequent items.
    for(auto it = L2.begin(); it != L2.end(); it++)
    {
        int fir = it->a;
        int sec = it->b;

        vector <int> vecLocal;
        // read corresponding itemToTID vector and find out common elements from them
        // this is compared against min_sup later
        // find out the occurrences for the particular pair using set_operation
        std::set_intersection(  itemId_TidMapping.at(fir).begin()+1, itemId_TidMapping.at(fir).end(),
                                itemId_TidMapping.at(sec).begin()+1, itemId_TidMapping.at(sec).end(),
                                std::back_inserter( vecLocal )  );

        if (vecLocal.size() >= minSupport){
            twoStruct.a = fir;
            twoStruct.b = sec;
            twoStruct.freq = vecLocal.size();
            C2.push_back(twoStruct);
            two_freq_itemset++;
            cout << "2 Frequent Items are: (" <<it->a << "," << it->b << ") " <<   "Freq is: " << vecLocal.size()<< endl;
        }
        vecLocal.clear();
    }
    cout << "two_freq_itemset:      " << two_freq_itemset << endl;
    //******************************************************************************************************************

    //Generate L3
    int delta=1;
    // FOLLOWING 2 FOR LOOPS GENERATE SET OF 3 ITEMS

    for (auto it = C2.begin(); it != C2.end(); it++,delta++ ) {     //delta is stride
        int base = it->a;

        auto it1 = C2.begin();                     // assign second iterator to same set *imp
        for (int k = 0; k < delta; k++) { it1++; }   //add a offset to second iterator and iterate over same set

        for (it1 = it1; it1 != C2.end(); it1++) {  //iterating over same set.
            if (base == it1->a) {
                    threeStruct.a = it->a;
                    threeStruct.b = it ->b;
                    threeStruct.c = it1->b;
                    threeStruct.freq = 0;
                    L3.push_back(threeStruct);
                    cout << "3 Items are: (" <<it->a << "," << it->b << "," << it1->b<< ") "  << endl;
            }
            else
                break;  // break internal for loop once base is not same as first entry in next pair. Increment *it
            }
    }

    // GENERATE C3 . Prune L3.

    for (auto it = L3.begin(); it != L3.end(); it++ ) {

        vector<int> vecLocal1, vecLocal2;
        std::set_intersection(itemId_TidMapping.at(it->a).begin() + 1, itemId_TidMapping.at(it->a).end(),
                              itemId_TidMapping.at(it->b).begin() + 1, itemId_TidMapping.at(it->b).end(),
                              std::back_inserter(vecLocal1));

        std::set_intersection(vecLocal1.begin(), vecLocal1.end(),
                              itemId_TidMapping.at(it->c).begin() + 1, itemId_TidMapping.at(it->c).end(),
                              std::back_inserter(vecLocal2));


        if (vecLocal2.size() >= minSupport) {
            three_freq_itemset++;
            threeStruct.a = it->a;
            threeStruct.b = it->b;
            threeStruct.c = it->c;
            threeStruct.freq = vecLocal2.size();
            C3.push_back(threeStruct);
            cout << "3 Frequent Items are: (" <<it->a << "," << it->b << "," << it->c<< ") " << "Freq is: " <<vecLocal2.size() << endl;
        }
        else{
            break;
        }
        vecLocal1.clear();  vecLocal2.clear();

    }
    cout << "three_freq_itemset:    " << three_freq_itemset << endl;
    //******************************************************************************************************************

    //Generate L4
    delta= 1;

    for(auto it2 = C3.begin(); it2 != C3.end(); it2++,delta++)
    {
        int c,d;
        auto it3 = C3.begin();                          // assign second iterator to same set *imp
        for (int k = 0; k < delta; k++) { it3++; }       //add a offset to second iterator and iterate over same set

        c = it2->a;
        d = it2->b;

        for (it3 = it3; it3 != C3.end(); it3++) {    //iterating over same set.
              if (c == it3->a && d == it3->b) {
                  fourStruct.a = it2->a;
                  fourStruct.b = it2->b;
                  fourStruct.c = it2->c;
                  fourStruct.d = it3->c;
                  fourStruct.freq =0;
                  L4.push_back(fourStruct);
                  cout << "4 Items are: (" <<it2->a << "," << it2->b << "," << it2->c<< "," << it3->c << ") " << "Freq is: " << endl;

              }
              else{
                  break; // break internal for loop to save iterations
              }
        }
    }

    // Generate C4. Prune L4
    for(auto it2 = L4.begin(); it2 != L4.end(); it2++) {
        vector<int> vecLocal1, vecLocal2,vecLocal3;
        std::set_intersection(itemId_TidMapping.at(it2->a).begin() + 1, itemId_TidMapping.at(it2->a).end(),
                              itemId_TidMapping.at(it2->b).begin() + 1, itemId_TidMapping.at(it2->b).end(),
                              std::back_inserter(vecLocal1));

        std::set_intersection(itemId_TidMapping.at(it2->c).begin() + 1, itemId_TidMapping.at(it2->c).end(),
                              itemId_TidMapping.at(it2->d).begin() + 1, itemId_TidMapping.at(it2->d).end(),
                              std::back_inserter(vecLocal2));

        std::set_intersection(vecLocal1.begin(), vecLocal1.end(),
                              vecLocal2.begin(), vecLocal2.end(),
                              std::back_inserter(vecLocal3));

        if (vecLocal3.size() >= minSupport) {
            four_freq_itemset++;
            fourStruct.a = it2->a;
            fourStruct.b = it2->b;
            fourStruct.c = it2->c;
            fourStruct.d = it2->d;
            fourStruct.freq = vecLocal3.size();
            C4.push_back(fourStruct);
            cout << "4 Frequent Items are: (" <<it2->a << "," << it2->b << "," << it2->c<< "," << it2->d << ") " << "Freq is: " <<vecLocal3.size() << endl;

        }
            vecLocal1.clear();  vecLocal2.clear();  vecLocal3.clear();

    }
    cout << "four_freq_itemset:     " << four_freq_itemset << endl;
    //******************************************************************************************************************
}   // end Execute



int main(int argc, char **argv){

    auto start = chrono::high_resolution_clock::now();

    Execute(argc);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> el = end - start;
    cout<<"Execution time is:     " << el.count() * 1000 << " mS " << endl;

    return 0;
}






