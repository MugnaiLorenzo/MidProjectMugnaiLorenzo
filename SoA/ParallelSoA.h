#ifndef MIDPROJECTMUGNAILORENZO_PARALLELSOA_H
#define MIDPROJECTMUGNAILORENZO_PARALLELSOA_H
#include <vector>
#include <string>
#include <map>

using namespace std;

class ParallelSoA {
public:
    explicit ParallelSoA(int n);

    void load_file(int n);

    void sequential_function();

    void generateBigrams(const std::string &text);

    void merge_bigrams(map<string, int> local_bigrams);

    void generateTrigrams(const std::string &text);

    void merge_trigrams(map<string, int> local_trigrams);

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


#endif //MIDPROJECTMUGNAILORENZO_PARALLELAOS_H
