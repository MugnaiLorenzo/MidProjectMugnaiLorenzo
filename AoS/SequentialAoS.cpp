#include "SequentialAoS.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "../include/gplot++.h"

SequentialAoS::SequentialAoS(const std::vector<std::string> &texts, int topN) : texts(texts), topN(topN) {
    processNgrams(2, bigrams); // Genera bigrammi
    processNgrams(3, trigrams); // Genera trigrammi
}

void SequentialAoS::processNgrams(int n, std::vector<Ngram> &ngrams) {
    for (const auto &text : texts) {
        generateNgrams(text, n, ngrams);
    }
}

void SequentialAoS::generateNgrams(const std::string &text, int n, std::vector<Ngram> &ngrams) {
    for (size_t i = 0; i < text.size() - n + 1; ++i) {
        // Estrai l'n-gramma
        std::string ngram = text.substr(i, n);

        // Converti in minuscolo
        std::transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);

        // Controlla che sia composto solo da lettere
        if (std::all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            // Cerca l'n-gramma nel vettore
            int index = findNgram(ngrams, ngram);

            if (index == -1) {
                // Aggiungi un nuovo oggetto Ngram al vettore
                Ngram newNgram(ngram);
                ngrams.push_back(newNgram);
            } else {
                // Incrementa il conteggio dell'n-gramma esistente
                ngrams[index].add();
            }
        }
    }
}

int SequentialAoS::findNgram(const std::vector<Ngram> &ngrams, const std::string &gram) const {
    for (size_t i = 0; i < ngrams.size(); ++i) {
        if (ngrams[i].getNgram() == gram) {
            return i;
        }
    }
    return -1; // Indica che non è stato trovato
}


void SequentialAoS::printTopNgramsGnuplot(const std::vector<Ngram> &ngrams, const std::string &outputFile) const {
    std::vector<Ngram> sorted_ngrams = ngrams;
    std::sort(sorted_ngrams.begin(), sorted_ngrams.end(),
              [](const Ngram &a, const Ngram &b) { return a.getCount() > b.getCount(); });

    sorted_ngrams.resize(std::min(static_cast<size_t>(topN), sorted_ngrams.size()));

    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile);

    for (size_t i = 0; i < sorted_ngrams.size(); ++i) {
        std::vector<int> x;
        for (int j = 0; j < sorted_ngrams[i].getCount(); j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, sorted_ngrams[i].getNgram());
    }

    gnuplot.set_title("Top " + std::to_string(topN) + " N-grams");
    gnuplot.set_xlabel("N-grams");
    gnuplot.set_ylabel("Frequency");
    gnuplot.set_xrange(1, topN);
    gnuplot.show();
}

void SequentialAoS::printResults() const {
    // Grafico per i bigrammi
    printTopNgramsGnuplot(bigrams, "./../Image/AoS/HistogramSequentialAoS_Bigrams_"+std::to_string(texts.size())+".png");

    // Grafico per i trigrammi
    printTopNgramsGnuplot(trigrams, "./../Image/AoS/HistogramSequentialAoS_Trigrams_"+std::to_string(texts.size())+".png");
}
