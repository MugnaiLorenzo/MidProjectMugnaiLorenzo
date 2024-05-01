#include "SequentialAoS.h"
#include <fstream>
#include <omp.h>
#include <algorithm>
#include "../include/gplot++.h"

SequentialAoS::SequentialAoS(vector<string> t) {
    texts = t;
    sequential_function();
}

void SequentialAoS::sequential_function() {
    double start_time, end_time;
    double t = 0;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        t = t + end_time - start_time;
        time_bi.push_back(t);
        start_time = omp_get_wtime();
        generateTrigrams(text);
        end_time = omp_get_wtime();
        t = t + end_time - start_time;
        time_tri.push_back(t);
    }
}

void SequentialAoS::generateBigrams(const std::string &text) {
    const int n = 2;
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            addBigrams(ngram);
        }
    }
}

bool SequentialAoS::addBigrams(string gram) {
    for (Ngram *b: bigrams) {
        if (b->getNgram() == gram) {
            b->add();
            return true;
        }
    }
    Ngram *b = new Ngram(gram);
    bigrams.push_back(b);
    return false;
}

void SequentialAoS::print_bi() {
    sort(bigrams.begin(), bigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramSequentialAoS_Bigrams.png");
    for (int i = 0; i < 30; i++) {
        std::vector<int> x;
        for (int j = 0; j < bigrams[i]->getCount(); j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, bigrams[i]->getNgram());
    }
    gnuplot.set_title("");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(0, 30);
    gnuplot.show();
}

void SequentialAoS::generateTrigrams(const std::string &text) {
    const int n = 3;
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            addTrigrams(ngram);
        }
    }
}

bool SequentialAoS::addTrigrams(string gram) {
    for (Ngram *b: trigrams) {
        if (b->getNgram() == gram) {
            b->add();
            return true;
        }
    }
    Ngram *b = new Ngram(gram);
    trigrams.push_back(b);
    return false;
}

void SequentialAoS::print_tri() {
    sort(trigrams.begin(), trigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramSequentialAoS_Trigrams.png");
    for (int i = 0; i < 30; i++) {
        std::vector<int> x;
        for (int j = 0; j < trigrams[i]->getCount(); j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, trigrams[i]->getNgram());
    }
    gnuplot.set_title("");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(0, 30);
    gnuplot.show();
}

double SequentialAoS::calc_average() {
    double tot = 0;
    for (int j = 0; j < time_bi.size(); j++) {
        tot = tot + time_bi[j];
    }
    average = tot / time_bi.size();
    return average;
}

vector<double> SequentialAoS::getTime() {
    return time_bi;
}
