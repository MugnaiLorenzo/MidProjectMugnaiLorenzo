#include "ParallelSoA.h"
#include <fstream>
#include <omp.h>
#include <algorithm>
#include "../include/gplot++.h"

ParallelSoA::ParallelSoA(vector<string> t) {
    texts = t;
    sequential_function();
}

void ParallelSoA::sequential_function() {
    double start_time, end_time;
    double t_bi = 0;
    double t_tri = 0;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        t_bi = t_bi + end_time - start_time;
        time_bi.push_back(t_bi);
        start_time = omp_get_wtime();
        generateTrigrams(text);
        end_time = omp_get_wtime();
        t_tri = t_tri + end_time - start_time;
        time_tri.push_back(t_tri);
    }
}

void ParallelSoA::generateBigrams(const std::string &text) {
    int n = 2;
    map<string, int> bigrams_local;
#pragma omp parallel default(none) private(bigrams_local) shared(text, n)
    {
#pragma omp for nowait
        for (int i = 0; i < text.length() - n + 1; ++i) {
            string ngram = text.substr(i, n);
            transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
            if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
                if (bigrams_local.find(ngram) != bigrams_local.end()) {
                    bigrams_local[ngram] += 1;
                } else {
                    bigrams_local[ngram] = 1;
                }
            }
        }
#pragma omp critical
        {
            merge_bigrams(bigrams_local);
        }
    }
}

void ParallelSoA::merge_bigrams(map<string, int> local_bigrams) {
    map<string, int>::iterator it;
    for (it = local_bigrams.begin(); it != local_bigrams.end(); it++) {
        if (bigrams.find(it->first) != bigrams.end()) {
            bigrams[it->first] += it->second;
        } else {
            bigrams[it->first] += it->second;
        }
    }
}

void ParallelSoA::generateTrigrams(const std::string &text) {
    int n = 3;
    map<string, int> trigrams_local;
#pragma omp parallel default(none) private(trigrams_local) shared(text, n)
    {
#pragma omp for nowait
        for (int i = 0; i < text.length() - n + 1; ++i) {
            string ngram = text.substr(i, n);
            transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
            if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
                if (trigrams_local.find(ngram) != trigrams_local.end()) {
                    trigrams_local[ngram] += 1;
                } else {
                    trigrams_local[ngram] = 1;
                }
            }
        }
#pragma omp critical
        {
            merge_trigrams(trigrams_local);
        }
    }
}

void ParallelSoA::merge_trigrams(map<string, int> local_trigrams) {
    map<string, int>::iterator it;
    for (it = local_trigrams.begin(); it != local_trigrams.end(); it++) {
        if (trigrams.find(it->first) != trigrams.end()) {
            trigrams[it->first] += it->second;
        } else {
            trigrams[it->first] = it->second;
        }
    }
}


double ParallelSoA::calc_average_bi() {
    double tot = 0;
    for (int j = 0; j < time_bi.size(); j++) {
        tot = tot + time_bi[j];
    }
    return tot / time_bi.size();
}

double ParallelSoA::calc_average_tri() {
    double tot = 0;
    for (int j = 0; j < time_tri.size(); j++) {
        tot = tot + time_tri[j];
    }
    return tot / time_tri.size();
}

void ParallelSoA::print_bi() {
    vector<pair<string, int> > pairs;
    for (auto &it: bigrams) {
        pairs.push_back(it);
    }
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/SoA/HistogramParallelSoA_Bigrams.png");
    int i = 0;
    for (auto &pair: pairs) {
        if (i < 30) {
            std::vector<int> x;
            for (int j = 0; j < pair.second; j++) {
                x.push_back(i + 1);
                x.push_back(i + 2);
            }
            gnuplot.histogram(x, 2, pair.first);
        }
        i++;
    }
    gnuplot.set_title("");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(0, 30);
    gnuplot.show();
}

void ParallelSoA::print_tri() {
    vector<pair<string, int> > pairs;
    for (auto &it: trigrams) {
        pairs.push_back(it);
    }
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/SoA/HistogramParallelSoA_Trigrams.png");
    int i = 0;
    for (auto &pair: pairs) {
        if (i < 30) {
            std::vector<int> x;
            for (int j = 0; j < pair.second; j++) {
                x.push_back(i + 1);
                x.push_back(i + 2);
            }
            gnuplot.histogram(x, 2, pair.first);
        }
        i++;
    }
    gnuplot.set_title("");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(0, 30);
    gnuplot.show();
}

vector<double> ParallelSoA::getTime_bi() {
    return time_bi;
}

vector<double> ParallelSoA::getTime_tri() {
    return time_tri;
}
