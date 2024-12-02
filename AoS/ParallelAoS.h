#ifndef PARALLELAOS_H
#define PARALLELAOS_H

#include <string>
#include <vector>
#include "Ngram.h"

class ParallelAoS {
public:
    // Costruttore
    ParallelAoS(std::vector<std::string> t, int topN);

// Funzione principale per la generazione parallela
    void parallel_function();

    // Funzione per stampare i risultati e generare i grafici
    void printResults() const;

private:
    // Generazione di n-grammi (bigrammi e trigrammi)
    void generateNgrams(const std::string &text, int n, std::vector<Ngram> &ngrams_local);

    // Fusione di n-grammi locali con i globali
    void mergeNgrams(const std::vector<Ngram> &local_ngrams, std::vector<Ngram> &global_ngrams);

    // Ricerca di un n-gramma
    int findNgram(const std::vector<Ngram> &ngrams, const std::string &ngram) const;

    // Generazione dei grafici per i n-grammi
    void printNgrams(const std::vector<Ngram> &ngrams, const std::string &outputFile) const;

    // Testi da analizzare
    std::vector<std::string> texts;

    // Contenitori per bigrammi e trigrammi
    std::vector<Ngram> bigrams;
    std::vector<Ngram> trigrams;

    // Tempi di esecuzione
    std::vector<double> time_bi;
    std::vector<double> time_tri;
};

#endif // PARALLELAOS_H
