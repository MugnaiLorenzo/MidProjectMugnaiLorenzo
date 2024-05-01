#include "ParallelAoS.h"
#include <omp.h>
#include <algorithm>
#include <fstream>

ParallelAoS::ParallelAoS(vector<string> t) {
    texts = t;
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
        time_bi.push_back(t);
        start_time = omp_get_wtime();
        generateTrigrams(text);
        end_time = omp_get_wtime();
        t = t + end_time - start_time;
        time_tri.push_back(t);
    }
}

void ParallelAoS::generateBigrams(const std::string &text) {
    vector<Ngram *> bigrams_local;
    int n = 2;
#pragma omp parallel private(bigrams_local) shared(text, n)
    {
#pragma omp for nowait
        for (int i = 0; i < text.length() - n + 1; ++i) {
            string ngram = text.substr(i, n);
            transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
            if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
                int k = ParallelAoS::find_Bigrams(bigrams_local, ngram);
                if (k == -1) {
                    bigrams_local.push_back(new Ngram(ngram));
                } else {
                    bigrams_local[k]->add();
                }
            }
        }
#pragma omp critical
        {
            merge_bigrams(bigrams_local);
        }
    }
}

void ParallelAoS::generateTrigrams(const std::string &text) {
    vector<Ngram *> trigrams_local;
    int n = 3;
#pragma omp parallel private(trigrams_local) shared(text, n)
    {
#pragma omp for nowait
        for (int i = 0; i < text.length() - n + 1; ++i) {
            string ngram = text.substr(i, n);
            transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
            if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
                int k = ParallelAoS::find_Bigrams(trigrams_local, ngram);
                if (k == -1) {
                    trigrams_local.push_back(new Ngram(ngram));
                } else {
                    trigrams_local[k]->add();
                }
            }
        }
#pragma omp critical
        {
            merge_trigrams(trigrams_local);
        }
    }
}

void ParallelAoS::merge_bigrams(vector<Ngram *> local_bigrams) {
    for (int i = 0; i < local_bigrams.size(); i++) {
        int k = find_Bigrams(bigrams, local_bigrams[i]->getNgram());
        if (k == -1) {
            Ngram *b = new Ngram(local_bigrams[i]->getNgram(), local_bigrams[i]->getCount());
            bigrams.push_back(b);
        } else {
            bigrams[k]->add(local_bigrams[i]->getCount());
        }
    }
}

void ParallelAoS::merge_trigrams(vector<Ngram *> local_trigrams) {
    for (int i = 0; i < local_trigrams.size(); i++) {
        int k = find_Trigrams(trigrams, local_trigrams[i]->getNgram());
        if (k == -1) {
            Ngram *b = new Ngram(local_trigrams[i]->getNgram(), local_trigrams[i]->getCount());
            trigrams.push_back(b);
        } else {
            trigrams[k]->add(local_trigrams[i]->getCount());
        }
    }
}

int ParallelAoS::find_Bigrams(vector<Ngram *> bigrams, string gram) {
    for (int k = 0; k < bigrams.size(); k++) {
        if (bigrams[k]->getNgram() == gram) {
            return k;
        }
    }
    return -1;
}

int ParallelAoS::find_Trigrams(vector<Ngram *> trigrams, string gram) {
    for (int k = 0; k < trigrams.size(); k++) {
        if (trigrams[k]->getNgram() == gram) {
            return k;
        }
    }
    return -1;
}

void ParallelAoS::print_bi() {
    sort(bigrams.begin(), bigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramParallelAoS_Bigrams.png");
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

void ParallelAoS::print_tri() {
    sort(trigrams.begin(), trigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramParallelAoS_Trigrams.png");
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

double ParallelAoS::calc_average() {
    double tot;
    for (int j = 0; j < time_bi.size(); j++) {
        tot = tot + time_bi[j];
    }
    average = tot / time_bi.size();
    return average;
}

vector<double> ParallelAoS::getTime() {
    return time_bi;
}
