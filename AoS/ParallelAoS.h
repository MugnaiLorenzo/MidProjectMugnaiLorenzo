#ifndef MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
#define MIDPROJECTMUGNAILORENZO_PARALLELAOS_H

#include <string>
#include <vector>
#include "Ngram.h"
#include "../include/gplot++.h"

using namespace std;

class ParallelAoS {
public:
    explicit ParallelAoS(int n);

    void load_file(int n);

    void sequential_function();

    void merge_bigrams(vector<Ngram *> local_bigrams);

    int find_Bigrams(vector<Ngram *> bi, string b);

    void printBi();

    void generateBigrams(const std::string &text);

    double calc_average();

    void print();

    vector<double> getTime();

private:
    vector<string> texts;
    vector<Ngram *> bigrams;
    vector<double> time;
    double average{};
};


#endif //MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
