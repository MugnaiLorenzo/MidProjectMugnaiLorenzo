#include "ParallelAoS.h"
#include <omp.h>
#include <algorithm>
#include <fstream>

ParallelAoS::ParallelAoS(int n) {
    load_file(n);
#pragma omp barrier
    sequential_function();
}

void ParallelAoS::load_file(int n) {
    string title;
#pragma omp parallel for shared(n)
    for (int i = 0; i < n; i++) {
        title = "./../Testi/book" + to_string(i) + ".txt";
        string text;
        ifstream newfile;
        while(!newfile.is_open()) {
            newfile.open(title, ios::in);
        }
        if (newfile.is_open()) {
            string currentLine;
            while (getline(newfile, currentLine)) {
                if (!currentLine.empty()) {
                    text += currentLine;
                    text += "\n";
                }
            }
            newfile.close();
        }
#pragma omp critical
        texts.push_back(text);
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

void ParallelAoS::sequential_function() {
    double start_time, end_time;
    double t = 0;
    int i = 0;
    for (const auto &text: texts) {
        start_time = omp_get_wtime();
        generateBigrams(text);
        end_time = omp_get_wtime();
        t = t + end_time - start_time;
        time.push_back(t);
        i = i + 1;
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

int ParallelAoS::find_Bigrams(vector<Ngram *> bigrams, string gram) {
    for (int k = 0; k < bigrams.size(); k++) {
        if (bigrams[k]->getNgram() == gram) {
            return k;
        }
    }
    return -1;
}

void ParallelAoS::printBi() {
    sort(bigrams.begin(), bigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramParallelAoS.png");
    for (int i = 0; i < 30; i++) {
        // cout << bigrams[i]->getCount() << endl;
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

double ParallelAoS::calc_average() {
    double tot;
    for (int j = 0; j < time.size(); j++) {
        tot = tot + time[j];
    }
    average = tot / time.size();
    return average;
}

vector<double> ParallelAoS::getTime() {
    return time;
}
