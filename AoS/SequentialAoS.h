#ifndef MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
#define MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <map>
#include <algorithm>
#include "Manage.h"

using namespace std;

class SequentialAoS {
public:
    explicit SequentialAoS(vector<string> t);

    void sequential_function();

    void generateBigrams(const std::string &text);

    double calc_average();

    void print();

    vector<double> getTime();


private:
    vector<string> texts;
    Manage m;
    vector<double> time;
    double average;
};


#endif //MIDPROJECTMUGNAILORENZO_SEQUENTIALAOS_H
