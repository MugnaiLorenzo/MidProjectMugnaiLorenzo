#include "ParallelAoS.h"
#include <omp.h>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "../include/gplot++.h"

// Costruttore
ParallelAoS::ParallelAoS(std::vector<std::string> t, int topN) : texts(std::move(t)) {
    parallel_function();
}

// Funzione parallela principale
void ParallelAoS::parallel_function() {
    double t_bi = 0, t_tri = 0;

#pragma omp parallel
    {
        std::vector<Ngram> local_ngrams;

        // Generazione parallela di bigrammi
#pragma omp for nowait reduction(+:t_bi)
        for (size_t i = 0; i < texts.size(); ++i) {
            double start = omp_get_wtime();
            generateNgrams(texts[i], 2, local_ngrams);
            t_bi += omp_get_wtime() - start;
        }

#pragma omp critical
        mergeNgrams(local_ngrams, bigrams);

        local_ngrams.clear();

        // Generazione parallela di trigrammi
#pragma omp for nowait reduction(+:t_tri)
        for (size_t i = 0; i < texts.size(); ++i) {
            double start = omp_get_wtime();
            generateNgrams(texts[i], 3, local_ngrams);
            t_tri += omp_get_wtime() - start;
        }

#pragma omp critical
        mergeNgrams(local_ngrams, trigrams);
    }

    time_bi.push_back(t_bi);
    time_tri.push_back(t_tri);
}

// Generazione di n-grammi (bigrammi e trigrammi)
void ParallelAoS::generateNgrams(const std::string &text, int n, std::vector<Ngram> &ngrams_local) {
    for (size_t i = 0; i <= text.size() - n; ++i) {
        std::string ngram = text.substr(i, n);
        std::transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (std::all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            int index = findNgram(ngrams_local, ngram);
            if (index == -1) {
                ngrams_local.emplace_back(ngram);
            } else {
                ngrams_local[index].add();
            }
        }
    }
}

// Fusione di n-grammi locali nei globali
void ParallelAoS::mergeNgrams(const std::vector<Ngram> &local_ngrams, std::vector<Ngram> &global_ngrams) {
    for (const auto &local_ngram : local_ngrams) {
        int index = findNgram(global_ngrams, local_ngram.getNgram());
        if (index == -1) {
            global_ngrams.push_back(local_ngram);
        } else {
            global_ngrams[index].add(local_ngram.getCount());
        }
    }
}

// Ricerca di un n-gramma
int ParallelAoS::findNgram(const std::vector<Ngram> &ngrams, const std::string &ngram) const {
    for (size_t i = 0; i < ngrams.size(); ++i) {
        if (ngrams[i].getNgram() == ngram) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Stampa e grafici dei risultati
void ParallelAoS::printResults() const {
    // Grafico per i bigrammi
    printNgrams(bigrams, "./../Image/AoS/HistogramParallelAoS_Bigrams.png");

    // Grafico per i trigrammi
    printNgrams(trigrams, "./../Image/AoS/HistogramParallelAoS_Trigrams.png");
}

// Funzione generica per la generazione dei grafici
void ParallelAoS::printNgrams(const std::vector<Ngram> &ngrams, const std::string &outputFile) const {
    auto sorted_ngrams = ngrams;
    std::sort(sorted_ngrams.begin(), sorted_ngrams.end(),
              [](const Ngram &a, const Ngram &b) { return a.getCount() > b.getCount(); });

    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile);

    for (size_t i = 0; i < std::min(static_cast<size_t>(10), sorted_ngrams.size()); ++i) {
        std::vector<int> x;
        for (int j = 0; j < sorted_ngrams[i].getCount(); j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, sorted_ngrams[i].getNgram());
    }

    gnuplot.set_title("N-grams Histogram");
    gnuplot.set_xlabel("N-grams");
    gnuplot.set_ylabel("Frequency");
    gnuplot.set_xrange(1, 10);
    gnuplot.show();
}
