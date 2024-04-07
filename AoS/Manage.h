#ifndef MIDPROJECTMUGNAILORENZO_MANAGE_H
#define MIDPROJECTMUGNAILORENZO_MANAGE_H

#include "Ngram.h"
#include <vector>
#include "../include/gplot++.h"
#include<algorithm>

using namespace std;

class Manage {
public:
    bool add_bigram(string gram);

    bool add_trigram(string gram);

    void printBi();

private:
//    map<string, Ngram *> bigrams;
    vector<Ngram *> bigrams;
    vector<Ngram *> trigrams;
};


#endif //MIDPROJECTMUGNAILORENZO_MANAGE_H
