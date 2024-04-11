#ifndef MIDPROJECTMUGNAILORENZO_SEQUENTIALSOA_H
#define MIDPROJECTMUGNAILORENZO_SEQUENTIALSOA_H
#include <vector>
#include <string>
#include <omp.h>
#include <algorithm>
#include <map>
#include "../include/gplot++.h"

using namespace std;

class SequentialSoA {
public:
    explicit SequentialSoA(vector<string> t);

    void sequential_function();

    void generateBigrams(const std::string &text);

    void generateTrigrams(const std::string &text);

    double calc_average_bi();

    double calc_average_tri();

    void print_bi();

    void print_tri();

    vector<double> getTime_bi();

    vector<double> getTime_tri();

private:
    vector<string> texts;
    vector<double> time_bi;
    vector<double> time_tri;
    map<string, int> bigrams;
    map<string, int> trigrams;
};


#endif //MIDPROJECTMUGNAILORENZO_SEQUENTIALSOA_H
