#ifndef MIDPROJECTMUGNAILORENZO_NGRAM_H
#define MIDPROJECTMUGNAILORENZO_NGRAM_H

#include <string>
#include <iostream>

using namespace std;

class Ngram {
public:
    explicit Ngram(string ngram);

    Ngram(string gram, int count);

    void add();

    void add(int n);

    string getNgram();

    int getCount();

private:
    string ngram;
    int count;
};


#endif //MIDPROJECTMUGNAILORENZO_NGRAM_H
