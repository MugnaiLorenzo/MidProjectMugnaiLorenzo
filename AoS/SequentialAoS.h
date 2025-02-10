#ifndef SEQUENTIALAOS_H
#define SEQUENTIALAOS_H

#include <string>
#include <vector>
#include "Ngram.h"

class SequentialAoS {
public:
    SequentialAoS(const std::vector<std::string> &texts, int topN);

// Stampa i risultati dei bigrammi e trigrammi usando Gnuplot
    void printResults() const;

private:
    void processNgrams(int n, std::vector<Ngram> &ngrams);
    void generateNgrams(const std::string &text, int n, std::vector<Ngram> &ngrams);
    int findNgram(const std::vector<Ngram> &ngrams, const std::string &gram) const;

    // Stampa i grafici con Gnuplot
    void printTopNgramsGnuplot(const std::vector<Ngram> &ngrams, const std::string &outputFile) const;

    std::vector<std::string> texts;
    std::vector<Ngram> bigrams;
    std::vector<Ngram> trigrams;
    int topN; // Numero massimo di n-grammi da stampare
};

#endif // SEQUENTIALAOS_H
