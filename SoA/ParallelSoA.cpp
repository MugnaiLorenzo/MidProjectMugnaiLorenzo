#include "ParallelSoA.h"

ParallelSoA::ParallelSoA(vector<string> t) {
    texts = t;
    ParallelSoA::sequential_function();
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
#pragma omp parallel for default(none) shared(text, n)
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            if (bigrams.find(ngram) != bigrams.end()) {
#pragma omp critical
                bigrams[ngram] += 1;
            } else {
#pragma omp critical
                bigrams[ngram] += 0;
            }
        }
    }
}

void ParallelSoA::generateTrigrams(const std::string &text) {
    int n = 3;
#pragma omp parallel for default(none) shared(text, n)
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            if (trigrams.find(ngram) != trigrams.end()) {
#pragma omp critical
                trigrams[ngram] += 1;
            } else {
#pragma omp critical
                trigrams[ngram] += 0;
            }
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
