#ifndef MIDPROJECTMUGNAILORENZO_MANAGEPARALLEL_H
#define MIDPROJECTMUGNAILORENZO_MANAGEPARALLEL_H


#include "Ngram.h"
#include <vector>
#include "../include/gplot++.h"
#include<algorithm>

using namespace std;

class ManageParallel {
public:
    bool add_bigram(string gram);

    bool add_trigram(string gram);

    void printBi();

    void printTri();

private:
    vector<Ngram *> bigrams;
    vector<Ngram *> trigrams;

};


#endif //MIDPROJECTMUGNAILORENZO_MANAGEPARALLEL_H

