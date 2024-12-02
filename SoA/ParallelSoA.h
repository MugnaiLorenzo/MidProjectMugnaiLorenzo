#ifndef PARALLELSOA_H
#define PARALLELSOA_H

#include <vector>
#include <string>
#include <map>

class ParallelSoA {
public:
    // Costruttore
    ParallelSoA(std::vector<std::string> t, int topN);

// Funzione principale
    void parallel_function();

    // Stampa dei risultati e generazione dei grafici
    void printResults() const;

private:
    // Generazione di n-grammi (bigrammi e trigrammi)
    void generateNgrams(int n, std::map<std::string, int> &ngrams);

    // Fusione dei risultati locali nei globali
    void mergeNgrams(const std::map<std::string, int> &local_ngrams, std::map<std::string, int> &global_ngrams);

    // Stampa e grafici degli n-grammi
    void printNgrams(const std::map<std::string, int> &ngrams, const std::string &outputFile) const;

    // Testi e tempi di esecuzione
    std::vector<std::string> texts;
    std::vector<double> time_bi;
    std::vector<double> time_tri;

    // Contenitori per bigrammi e trigrammi
    std::map<std::string, int> bigrams;
    std::map<std::string, int> trigrams;
};

#endif // PARALLELSOA_H
