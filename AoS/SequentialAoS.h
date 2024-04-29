#ifndef MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
#define MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H

#include <string>
#include <vector>
#include "Ngram.h"

using namespace std;

class SequentialAoS {
public:
    explicit SequentialAoS(int n);

    void load_file(int n);

    void sequential_function();

    void generateBigrams(const std::string &text);

    bool addBigrams(string gram);

    void printBi();

    double calc_average();

    void print();

    vector<double> getTime();

private:
    vector<string> texts;
    vector<Ngram *> bigrams;
    vector<double> time;
    double average{};
};


#endif //MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
