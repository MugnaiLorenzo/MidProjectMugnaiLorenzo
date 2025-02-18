#include "SequentialSoA.h"
#include <algorithm>
#include <fstream>
#include "../include/gplot++.h"

// Costruttore
SequentialSoA::SequentialSoA(std::vector<std::string> t, int topN) : texts(std::move(t)), topN(topN) {
    processNgrams(2, bigrams);
    processNgrams(3, trigrams);
}

void SequentialSoA::processNgrams(int n, std::map<std::string, int> &ngrams) {
    for (const auto &text : texts) {
        generateNgrams(text, n, ngrams);
    }
}

// Funzione generica per la generazione di n-grammi
void SequentialSoA::generateNgrams(const std::string &text, int n, std::map<std::string, int> &ngrams) {
    for (size_t i = 0; i <= text.size() - n; ++i) {
        std::string ngram = text.substr(i, n);
        std::transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (std::all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            ngrams[ngram]++;
        }
    }
}

// Funzione generica per la stampa e la generazione dei grafici
void SequentialSoA::printNgrams(const std::map<std::string, int> &ngrams, const std::string &outputFile) const {
    std::vector<std::pair<std::string, int>> pairs(ngrams.begin(), ngrams.end());
    std::sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile);

    int i = 0;
    for (const auto &pair : pairs) {
        if (i < topN) {
            std::vector<int> x;
            for (int j = 0; j < pair.second; j++) {
                x.push_back(i + 1);
                x.push_back(i + 2);
            }
            gnuplot.histogram(x, 2, pair.first);
        }
        i++;
    }

    gnuplot.set_title("N-grams Histogram");
    gnuplot.set_xlabel("N-grams");
    gnuplot.set_ylabel("Frequency");
    gnuplot.set_xrange(1, topN);
    gnuplot.show();
}

// Stampa dei risultati (bigrammi e trigrammi)
void SequentialSoA::printResults() const {
    // Grafico per i bigrammi
    printNgrams(bigrams, "./../Image/SoA/HistogramSequentialSoA_Bigrams_"+std::to_string(texts.size())+".png");

    // Grafico per i trigrammi
    printNgrams(trigrams, "./../Image/SoA/HistogramSequentialSoA_Trigrams_"+std::to_string(texts.size())+".png");
}
