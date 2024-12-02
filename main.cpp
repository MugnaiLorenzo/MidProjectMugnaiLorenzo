#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
#include "SoA/SequentialSoA.h"
#include "SoA/ParallelSoA.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono> // Per misurare il tempo di esecuzione
#include <omp.h>  // Per configurare i thread

using namespace std;

// Funzione per caricare i file di testo
void load_file(int n, vector<string> &texts) {
    for (int i = 0; i < n; ++i) {
        string filename = "./../Testi/book" + to_string(i) + ".txt";
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

// Funzione generica per eseguire SequentialAoS o SequentialSoA
template <typename SequentialType>
void execute_sequential(const vector<string> &texts, int topN, const string &method_name) {
    cout << "Esecuzione sequenziale (" << method_name << ")...\n";
    auto start_time = chrono::high_resolution_clock::now();

    SequentialType sequential(texts, topN);

    auto end_time = chrono::high_resolution_clock::now();
    sequential.printResults();
    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << "Tempo di esecuzione sequenziale (" << method_name << "): "
         << elapsed_time.count() << " secondi.\n";
}

// Funzione generica per eseguire ParallelAoS o ParallelSoA
template <typename ParallelType>
void execute_parallel(const vector<string> &texts, int max_threads, const string &method_name, int topN) {
    cout << "\nEsecuzione parallela (" << method_name << ")...\n";
    for (int threads = 2; threads <= max_threads; threads += 2) {
        omp_set_num_threads(threads);
        auto start_time = chrono::high_resolution_clock::now();

        ParallelType parallel(texts, topN);
        auto end_time = chrono::high_resolution_clock::now();
        if (threads == 2) {
            parallel.printResults(); // Stampa i risultati solo alla prima esecuzione
        }
        chrono::duration<double> elapsed_time = end_time - start_time;

        cout << "Threads: " << threads
             << ", Tempo di esecuzione parallela (" << method_name << "): "
             << elapsed_time.count() << " secondi.\n";
    }
}

int main() {
    // Numero di file da caricare
    int n_books = 1;
    // Numero massimo di n-grammi da stampare
    int topN = 10;

    // Carica i file di testo
    vector<string> texts;
    load_file(n_books, texts);

    if (texts.empty()) {
        cerr << "Errore: nessun file è stato caricato. Terminazione del programma." << endl;
        return 1;
    }

    cout << "Caricati " << texts.size() << " file di testo.\n";

    // Esecuzione sequenziale AoS
    execute_sequential<SequentialAoS>(texts, topN, "AoS");

    // Esecuzione sequenziale SoA
    execute_sequential<SequentialSoA>(texts, topN, "SoA");

    // Esecuzione parallela AoS
    int max_threads = omp_get_max_threads();
    execute_parallel<ParallelAoS>(texts, max_threads, "AoS", topN);

    // Esecuzione parallela SoA
    execute_parallel<ParallelSoA>(texts, max_threads, "SoA", topN);

    return 0;
}
