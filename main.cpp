#include <iostream>
#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
#include "SoA/SequentialSoA.h"
#include "SoA/ParallelSoA.h"
#include "include/gplot++.h"
#include <fstream>
#include <omp.h>

void load_file(int n, vector<string> *texts) {
    string title;
    for (int i = 0; i < n; i++) {
        title = "./../Testi/book" + to_string(i) + ".txt";
        string text;
        ifstream newfile;
        while (!newfile.is_open()) {
            newfile.open(title, ios::in);
        }
        if (newfile.is_open()) {
            string currentLine;
            while (getline(newfile, currentLine)) {
                if (!currentLine.empty()) {
                    text += currentLine;
                    text += "\n";
                }
            }
            newfile.close();
        }
        texts->push_back(text);
    }
}

void sequential(vector<string> texts, string &txtAoS, string &txtSoA, vector<pair<double, int> > &sSoA_time,
                vector<pair<double, int> > &sAoS_time) {
    double start, end;
    start = omp_get_wtime();
    SequentialSoA *sSoA = new SequentialSoA(texts);
    end = omp_get_wtime();
    txtSoA += "Tempo operazione bigrammi/trigrammi Sequenziale SoA: " + to_string(end - start) + "\n";
    sSoA_time.push_back(make_pair(end - start, 1));
    start = omp_get_wtime();
    SequentialAoS *sAoS = new SequentialAoS(texts);
    end = omp_get_wtime();
    txtAoS += "Tempo operazione bigrammi/trigrammi Sequenziale AoS: " + to_string(end - start) + "\n";
    sAoS_time.push_back(make_pair(end - start, 1));
    sAoS->print_bi();
    sAoS->print_tri();
    sSoA->print_bi();
    sSoA->print_tri();
}

void parallel(vector<string> texts, string &txtAoS, string &txtSoA, vector<pair<double, int> > &pSoA_time,
              vector<pair<double, int> > &pAoS_time, int n_th) {
    omp_set_num_threads(n_th);
    double start, end;
    start = omp_get_wtime();
    ParallelAoS *pAoS = new ParallelAoS(texts);
    end = omp_get_wtime();
    txtAoS += "Tempo operazione bigrammi/trigrammi Sequenziale AoS: " + to_string(end - start);
    txtAoS += " con numero threads: " + to_string(n_th) + "\n";
    pAoS_time.push_back(make_pair(end - start, n_th));
    start = omp_get_wtime();
    ParallelSoA *pSoA = new ParallelSoA(texts);
    end = omp_get_wtime();
    txtSoA += "Tempo operazione bigrammi/trigrammi Sequenziale SoA: " + to_string(end - start);
    txtSoA += " con numero threads: " + to_string(n_th) + "\n";
    pSoA_time.push_back(make_pair(end - start, n_th));
}

void draw_speedUp(string file, vector<pair<double, int> > time) {
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png(file);
    vector<double> y;
    vector<double> x;
    for (const auto &pair: time) {
        y.push_back(time[0].first / pair.first);
        x.push_back(pair.second);
    }
    gnuplot.plot(x, y, "title1");
    gnuplot.set_xrange(0, 12);
    gnuplot.show();
}

int main() {
    int n_book = 4;
    int max_th = omp_get_max_threads();
    vector<pair<double, int> > SoA_time, AoS_time;
    vector<string> texts;
    string txtAoS, txtSoA;
    load_file(n_book, &texts);
    sequential(texts, txtAoS, txtSoA, SoA_time, AoS_time);
    for (int num_th = 0; num_th <= max_th; num_th = num_th + 2) {
        if (num_th != 0) {
            parallel(texts, txtAoS, txtSoA, SoA_time, AoS_time, num_th);
        }
    }
    ParallelAoS *pAoS = new ParallelAoS(texts);
    ParallelSoA *pSoA = new ParallelSoA(texts);
    cout << txtAoS << endl;
    cout << txtSoA << endl;
    pAoS->print_bi();
    pAoS->print_tri();
    pSoA->print_bi();
    pSoA->print_tri();
    draw_speedUp("./../Image/AoS/speedUp.png", AoS_time);
    draw_speedUp("./../Image/SoA/speedUp.png", SoA_time);
    return 0;
}
