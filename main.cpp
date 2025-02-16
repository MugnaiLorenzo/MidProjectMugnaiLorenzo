#include "Benchmark.h"
#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
#include "SoA/SequentialSoA.h"
#include "SoA/ParallelSoA.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>

using namespace std;

// Funzione per caricare i file di testo
void load_files(int n, vector<string> &texts) {
    texts.clear(); // Svuota il vettore prima di ricaricare i file
    for (int i = 0; i < n; ++i) {
        string filename = "./../Testi/book" + to_string(i % 29) + ".txt"; // Cicla sui 29 libri disponibili
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Errore: impossibile aprire il file " << filename << endl;
            continue;
        }
        ostringstream buffer;
        buffer << file.rdbuf();
        texts.push_back(buffer.str());
    }
}

// Funzione generica per misurare i tempi delle implementazioni sequenziali
template<typename SequentialType>
double measureSequential(const vector<string> &texts, const string &method_name, int topN) {
    auto start_time = chrono::high_resolution_clock::now();
    SequentialType sequential(texts, topN);
    auto end_time = chrono::high_resolution_clock::now();
    sequential.printResults();
    return chrono::duration<double>(end_time - start_time).count();
}

// Funzione generica per misurare i tempi delle implementazioni parallele
template<typename ParallelType>
double measureParallel(const vector<string> &texts, const string &method_name, int topN, bool vectorized = false, int threads = 1) {
    omp_set_num_threads(threads);
    auto start_time = chrono::high_resolution_clock::now();
    ParallelType parallel(texts, topN, vectorized);
    auto end_time = chrono::high_resolution_clock::now();
    return chrono::duration<double>(end_time - start_time).count();
}

int main() {
    int base_books = 1;  // Numero iniziale di libri
    int max_iterations = 1; // Numero massimo di moltiplicazioni di 29 (es. 29, 58, 87, 116, ...)
    int topN = 10; // Numero massimo di n-grammi da considerare
    int max_threads = omp_get_max_threads();

    cout << "************ BENCHMARK N-GRAMS ************\n";

    for (int i = 1; i <= max_iterations; ++i) {
        int n_books = base_books * i * 2;
        vector<string> texts;
        load_files(n_books, texts);

        if (texts.empty()) {
            cerr << "Errore: Nessun file caricato.\n";
            return 1;
        }

        cout << "\n====== ANALISI CON " << n_books << " FILE DI TESTO ======\n";
        Benchmark benchmark;

        // SEQUENZIALE AoS
        cout << "\n--- MODALITA' AoS ---\n";
        double seq_time_aos = measureSequential<SequentialAoS>(texts, "SequentialAoS", topN);
        cout << "Tempo di esecuzione Sequenziale AoS: " << seq_time_aos << " secondi\n";
        benchmark.addResult("ParallelAoS",1,seq_time_aos);
        // PARALLELO AoS
        for (int threads = 2; threads <= max_threads; threads += 2) {
            double par_time_aos = measureParallel<ParallelAoS>(texts, "ParallelAoS", topN, false, threads);
            cout << "Parallel AoS con " << threads << " threads: " << par_time_aos << " secondi\n";
            double speedup_aos = seq_time_aos / par_time_aos;
            cout << "Speedup AoS: " << speedup_aos << "x\n";
            benchmark.addResult("ParallelAoS", threads, par_time_aos);
        }

        // SEQUENZIALE SoA
        cout << "\n--- MODALITA' SoA ---\n";
        double seq_time_soa = measureSequential<SequentialSoA>(texts, "SequentialSoA", topN);
        cout << "Tempo di esecuzione Sequenziale SoA: " << seq_time_soa << " secondi\n";
        benchmark.addResult("ParallelSoA",1,seq_time_soa);
        benchmark.addResult("VectorizedSoA",1,seq_time_soa);

        // PARALLELO SoA
        for (int threads = 2; threads <= max_threads; threads += 2) {
            double par_time_soa = measureParallel<ParallelSoA>(texts, "ParallelSoA", topN, false, threads);
            cout << "Parallel SoA con " << threads << " threads: " << par_time_soa << " secondi\n";
            double speedup_soa = seq_time_soa / par_time_soa;
            cout << "Speedup SoA: " << speedup_soa << "x\n";
            benchmark.addResult("ParallelSoA", threads, par_time_soa);
        }

        // PARALLELO SoA VETTORIZZATO
        cout << "\n--- MODALITA' SoA VETTORIZZATA ---\n";
        for (int threads = 2; threads <= max_threads; threads += 2) {
            double vec_time_soa = measureParallel<ParallelSoA>(texts, "VectorizedSoA", topN, true, threads);
            cout << "Parallel SoA Vettorizzato con " << threads << " threads: " << vec_time_soa << " secondi\n";
            double speedup_vec_soa = seq_time_soa / vec_time_soa;
            cout << "Speedup SoA Vettorizzato: " << speedup_vec_soa << "x\n";
            benchmark.addResult("VectorizedSoA", threads, vec_time_soa);
        }

        // Generazione grafici per i tempi di esecuzione e speedup
        benchmark.plotExecutionTimes("./../Image/Plot/ExecutionTimes_", to_string(n_books));
        benchmark.plotSpeedup("./../Image/Plot/Speedup_", to_string(n_books));
    }

    cout << "\n************ TEST COMPLETATI ************\n";
    return 0;
}
