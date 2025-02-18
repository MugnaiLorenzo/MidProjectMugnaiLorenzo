#ifndef SEQUENTIALSOA_H
#define SEQUENTIALSOA_H

#include <vector>
#include <string>
#include <map>

class SequentialSoA {
public:
    // Costruttore
    explicit SequentialSoA(std::vector<std::string> t);

    SequentialSoA(std::vector<std::string> t, int topN);

    SequentialSoA(const std::vector<std::string> vector1, int i, bool b);

// Funzione principale
    void sequential_function();

    // Stampa i risultati (grafici e output)
    void printResults() const;

    // Calcolo della media dei tempi di esecuzione
    double calc_average_bi();
    double calc_average_tri();

    // Recupero dei tempi
    std::vector<double> getTime_bi();
    std::vector<double> getTime_tri();

private:
    // Funzione generica per la generazione di n-grammi
    void generateNgrams(const std::string &text, int n, std::map<std::string, int> &ngrams);

    // Funzione generica per la stampa e la generazione dei grafici
    void printNgrams(const std::map<std::string, int> &ngrams, const std::string &outputFile) const;

    // Testi e tempi
    std::vector<std::string> texts;
    std::vector<double> time_bi;
    std::vector<double> time_tri;

    // N-grammi
    std::map<std::string, int> bigrams;
    std::map<std::string, int> trigrams;

    void processNgrams(int n, std::map<std::string, int> &ngrams);

    int topN;
};

#endif // SEQUENTIALSOA_H
