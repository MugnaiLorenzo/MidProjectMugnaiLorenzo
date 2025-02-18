#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>
#include <map>

class Benchmark {
public:
    // Aggiunge un risultato al benchmark
    void addResult(const std::string &method, int threads, double execution_time);

    // Calcola il speed-up rispetto al sequenziale
    std::map<std::string, std::vector<double>> calculateSpeedup();

    // Genera un grafico per i tempi di esecuzione
    void plotExecutionTimes(const std::string &outputFile, std::string n_book);

    // Genera un grafico per il speed-up
    void plotSpeedup(const std::string &outputFile, std::string n_book);

    // Genera un grafico comparativo per tutti i metodi (Execution Time)
    void plotExecutionTimesComparison(const std::string &outputFile, std::string n_book);

    // Genera un grafico comparativo per tutti i metodi (Speedup)
    void plotSpeedupComparison(const std::string &outputFile, std::string n_book);

private:
    // Dati raccolti
    std::map<std::string, std::vector<std::pair<int, double>>> results;
};

#endif // BENCHMARK_H
