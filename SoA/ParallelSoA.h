#ifndef PARALLELSOA_H
#define PARALLELSOA_H

#include <vector>
#include <string>
#include <map>

class ParallelSoA {
public:
    // Costruttore
    ParallelSoA(std::vector<std::string> t, int topN, bool use_vectorization = false);

// Funzione principale
    void parallel_function();

    // Stampa dei risultati e generazione dei grafici
    void printResults() const;

private:
    // Generazione di n-grammi
    void generateNgrams(int n, std::map<std::string, int> &ngrams);
    void generateNgramsVectorized(int n, std::map<std::string, int> &ngrams);

    // Fusione dei risultati locali
    void mergeNgrams(const std::map<std::string, int> &local_ngrams, std::map<std::string, int> &global_ngrams);

    // Stampa e grafici
    void printNgrams(const std::map<std::string, int> &ngrams, const std::string &outputFile) const;

    // Testi e modalità
    std::vector<std::string> texts;
    bool vectorized;

    // Contenitori per bigrammi e trigrammi
    std::map<std::string, int> bigrams;
    std::map<std::string, int> trigrams;
};

#endif // PARALLELSOA_H
