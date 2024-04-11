#include "ParallelAoS.h"

ParallelAoS::ParallelAoS(vector<string> t) {
    texts = t;
    m = *new ManageParallel();
    sequential_function();
}


void ParallelAoS::sequential_function() {
    double start_time, end_time;
    double t = 0;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        t = t + end_time - start_time;
        time.push_back(t);
    }
}

void ParallelAoS::generateBigrams(const std::string &text) {
    int n = 2;
#pragma omp parallel for default(none) shared(text, n)
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            m.add_bigram(ngram);
        }
    }
}

double ParallelAoS::calc_average() {
    double tot;
    for (int j = 0; j < time.size(); j++) {
        tot = tot + time[j];
    }
    average = tot / time.size();
    return average;
}

void ParallelAoS::print() {
    m.printBi();
}

vector<double> ParallelAoS::getTime() {
    return time;
}
