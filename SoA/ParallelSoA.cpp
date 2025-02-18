#include "ParallelSoA.h"
#include <fstream>
#include <omp.h>
#include <algorithm>
#include <immintrin.h> // Per le istruzioni SIMD
#include "../include/gplot++.h"

// Costruttore
ParallelSoA::ParallelSoA(std::vector<std::string> t, int topN, bool use_vectorization)
        : texts(std::move(t)), vectorized(use_vectorization), topN(topN){
    parallel_function();
}

// Funzione principale parallela
void ParallelSoA::parallel_function() {
    // Esecuzione parallela per bigrammi
    if (vectorized) {
        generateNgramsVectorized(2, bigrams);
    } else {
        generateNgrams(2, bigrams);
    }

    // Esecuzione parallela per trigrammi
    if (vectorized) {
        generateNgramsVectorized(3, trigrams);
    } else {
        generateNgrams(3, trigrams);
    }
}

// Funzione generica per generare n-grammi in modalità classica
void ParallelSoA::generateNgrams(int n, std::map<std::string, int> &ngrams) {
    std::map<std::string, int> local_ngrams;

#pragma omp parallel default(none) private(local_ngrams) shared(texts, n, ngrams)
    {
#pragma omp for nowait
        for (size_t t = 0; t < texts.size(); ++t) {
            for (size_t i = 0; i <= texts[t].size() - n; ++i) {
                std::string ngram = texts[t].substr(i, n);
                std::transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
                if (std::all_of(ngram.begin(), ngram.end(), ::isalpha)) {
                    local_ngrams[ngram]++;
                }
            }
        }

#pragma omp critical
        mergeNgrams(local_ngrams, ngrams);
    }
}

// Funzione generica per generare n-grammi in modalità vettoriale
void ParallelSoA::generateNgramsVectorized(int n, std::map<std::string, int> &ngrams) {
    std::map<std::string, int> local_ngrams;

#pragma omp parallel
    {
        std::map<std::string, int> thread_local_ngrams;

#pragma omp for nowait
        for (size_t t = 0; t < texts.size(); ++t) {
            const char *data = texts[t].c_str();
            size_t text_size = texts[t].size();

#pragma omp simd
            for (size_t i = 0; i <= text_size - n; ++i) {
                // Creiamo direttamente la stringa da un puntatore
                const char *ngram_ptr = &data[i];

                // Evitiamo concatenazioni e operazioni costose
                thread_local_ngrams[std::string(ngram_ptr, n)]++;
            }
        }

        // Fusione thread-safe dei risultati
#pragma omp critical
        for (const auto &entry : thread_local_ngrams) {
            ngrams[entry.first] += entry.second;
        }
    }
}



// Funzione generica per fondere i risultati locali
void
ParallelSoA::mergeNgrams(const std::map<std::string, int> &local_ngrams, std::map<std::string, int> &global_ngrams) {
    for (const auto &entry: local_ngrams) {
        global_ngrams[entry.first] += entry.second;
    }
}

// Funzione per stampare e generare grafici degli n-grammi
void ParallelSoA::printNgrams(const std::map<std::string, int> &ngrams, const std::string &outputFile) const {
    std::vector<std::pair<std::string, int>> sorted_ngrams(ngrams.begin(), ngrams.end());
    std::sort(sorted_ngrams.begin(), sorted_ngrams.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });

    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile);

    int i = 0;
    for (const auto &pair: sorted_ngrams) {
        if (i >= 10) break;
        std::vector<int> x;
        for (int j = 0; j < pair.second; j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, pair.first);
        i++;
    }

    gnuplot.set_title("N-grams Histogram");
    gnuplot.set_xlabel("N-grams");
    gnuplot.set_ylabel("Frequency");
    gnuplot.set_xrange(1, topN);
    gnuplot.show();
}

// Stampa dei risultati per bigrammi e trigrammi
void ParallelSoA::printResults() const {
    // Grafico per bigrammi
    printNgrams(bigrams, "./../Image/SoA/HistogramParallelSoA_Bigrams_"+std::to_string(texts.size())+".png");

    // Grafico per trigrammi
    printNgrams(trigrams, "./../Image/SoA/HistogramParallelSoA_Trigrams_"+std::to_string(texts.size())+".png");
}
