#ifndef MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
#define MIDPROJECTMUGNAILORENZO_PARALLELAOS_H

#include <string>
#include <vector>
#include "Ngram.h"
#include "../include/gplot++.h"

using namespace std;

class ParallelAoS {
public:
    ParallelAoS(vector<string> texts);

    void sequential_function();

    void merge_bigrams(vector<Ngram *> local_bigrams);

    void merge_trigrams(vector<Ngram *> local_trigrams);

    int find_Bigrams(vector<Ngram *> bi, string b);

    int find_Trigrams(vector<Ngram *> trigrams, string gram);

    void print_bi();

    void print_tri();

    void generateBigrams(const std::string &text);

    void generateTrigrams(const std::string &text);

    double calc_average();

    vector<double> getTime();

private:
    vector<string> texts;
    vector<double> time_bi;
    vector<double> time_tri;
    vector<Ngram *> bigrams;
    vector<Ngram *> trigrams;
    double average{};
};


#endif //MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
