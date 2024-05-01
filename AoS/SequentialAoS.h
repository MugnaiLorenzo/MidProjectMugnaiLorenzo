#ifndef MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
#define MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H

#include <string>
#include <vector>
#include "Ngram.h"

using namespace std;

class SequentialAoS {
public:
    SequentialAoS(vector<string> t);

    void sequential_function();

    void generateBigrams(const std::string &text);

    void generateTrigrams(const std::string &text);

    bool addBigrams(string gram);

    bool addTrigrams(string gram);

    void print_bi();

    void print_tri();

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


#endif //MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
