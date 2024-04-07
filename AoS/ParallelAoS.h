#ifndef MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
#define MIDPROJECTMUGNAILORENZO_PARALLELAOS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <map>
#include <algorithm>
#include "ManageParallel.h"

using namespace std;

class ParallelAoS {
public:
    explicit ParallelAoS(vector<string> t);

    void sequential_function();

    void generateBigrams(const std::string &text);

    double calc_average();

    void print();

    vector<double> getTime();


private:
    vector<string> texts;
    ManageParallel m;
    vector<double> time;
    double average;
};


#endif //MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
