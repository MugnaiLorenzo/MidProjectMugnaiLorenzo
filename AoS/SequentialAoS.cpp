#include "SequentialAoS.h"

SequentialAoS::SequentialAoS(vector<string> t) {
    texts = t;
    m = *new Manage();
    SequentialAoS::sequential_function();
}

void SequentialAoS::sequential_function() {
    double start_time, end_time;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        time.push_back(end_time - start_time);
    }
}

void SequentialAoS::generateBigrams(const std::string &text) {
    int n = 2;
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            m.add_bigram(ngram);
        }
    }
}

double SequentialAoS::calc_average() {
    double tot = 0;
    for (int j = 0; j < time.size(); j++) {
        tot = tot + time[j];
    }
    average = tot / time.size();
    return average;
}

void SequentialAoS::print() {
    m.printBi();
}

vector<double> SequentialAoS::getTime() {
    return time;
}
