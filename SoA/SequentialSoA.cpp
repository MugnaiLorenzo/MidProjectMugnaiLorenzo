#include "SequentialSoA.h"

SequentialSoA::SequentialSoA(vector<string> t) {
    texts = t;
    SequentialSoA::sequential_function();
}

void SequentialSoA::sequential_function() {
    double start_time, end_time;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        time_bi.push_back(end_time - start_time);
        start_time = omp_get_wtime();
        generateTrigrams(text);
        end_time = omp_get_wtime();
        time_tri.push_back(end_time - start_time);
    }
}

void SequentialSoA::generateBigrams(const std::string &text) {
    int n = 2;
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            if (bigrams.find(ngram) != bigrams.end()) {
                bigrams[ngram] += 1;
            } else {
                bigrams[ngram] += 0;
            }
        }
    }
}

void SequentialSoA::generateTrigrams(const std::string &text) {
    int n = 3;
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            if (trigrams.find(ngram) != trigrams.end()) {
                trigrams[ngram] += 1;
            } else {
                trigrams[ngram] += 0;
            }
        }
    }
}

double SequentialSoA::calc_average_bi() {
    double tot = 0;
    for (int j = 0; j < time_bi.size(); j++) {
        tot = tot + time_bi[j];
    }
    return tot / time_bi.size();
}

double SequentialSoA::calc_average_tri() {
    double tot = 0;
    for (int j = 0; j < time_tri.size(); j++) {
        tot = tot + time_tri[j];
    }
    return tot / time_tri.size();
}

void SequentialSoA::print_bi() {
    vector<pair<string, int> > pairs;
    for (auto &it: bigrams) {
        pairs.push_back(it);
    }
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/SoA/sHistogramSequentialSoA_Bigrams.png");
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

void SequentialSoA::print_tri() {
    vector<pair<string, int> > pairs;
    for (auto &it: trigrams) {
        pairs.push_back(it);
    }
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/SoA/HistogramSequentialSoA_Trigrams.png");
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

vector<double> SequentialSoA::getTime_bi() {
    return time_bi;
}

vector<double> SequentialSoA::getTime_tri() {
    return time_tri;
}
