#include <iostream>
#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
#include "SoA/SequentialSoA.h"
#include "SoA/ParallelSoA.h"
#include "include/gplot++.h"
#include <fstream>
#include <omp.h>

void draw(vector<double> time1, string title1, vector<double> time2, string title2, string file) {
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png(file);
    gnuplot.plot(time1, title1);
    gnuplot.plot(time2, title2);
    gnuplot.show();
}

void Aos(int n_book) {
    string temp = "";
    double sAoS_time, pAoS_time, start, end;
    start = omp_get_wtime();
    SequentialAoS *s = new SequentialAoS(n_book);
    end = omp_get_wtime();
    sAoS_time = end - start;
    start = omp_get_wtime();
    ParallelAoS *p = new ParallelAoS(n_book);
    end = omp_get_wtime();
    pAoS_time = end - start;
    temp += "Tempo operazione bigrammi Sequenziale AoS: " + to_string(sAoS_time) + "\n";
    temp += "Tempo operazione bigrammi Parallelo AoS: " + to_string(pAoS_time) + "\n";
    cout << temp << endl;
    s->printBi();
    p->printBi();
    draw(p->getTime(), "SequentialAoS", s->getTime(), "ParallelAoS", "./../Image/AoS/Aos_Parallel_vs_Sequential.png");
}

void SoA(int n_book) {
    double sSoA_time, pSoA_time, start, end;
    string temp = "";
    start = omp_get_wtime();
    SequentialSoA *sSoA = new SequentialSoA(n_book);
    end = omp_get_wtime();
    sSoA_time = end - start;
    start = omp_get_wtime();
    ParallelSoA *pSoA = new ParallelSoA(n_book);
    end = omp_get_wtime();
    pSoA_time = end - start;
    sSoA->print_bi();
    sSoA->print_tri();
    pSoA->print_bi();
    pSoA->print_tri();
    draw(sSoA->getTime_bi(), "SequentialSoA", pSoA->getTime_bi(), "ParallelSoA",
         "./../Image/SoA/SoA_Parallel_vs_Sequential_Bi.png");
    draw(sSoA->getTime_tri(), "SequentialSoA", pSoA->getTime_tri(), "ParallelSoA",
         "./../Image/SoA/SoA_Parallel_vs_Sequential_Tri.png");
    temp += "Tempo operazione bigrammi/trigrammi Sequenziale SoA: " + to_string(sSoA_time) + "\n";
    temp += "Tempo operazione bigrammi/trigrammi Parallelo SoA: " + to_string(pSoA_time)  + "\n";
    cout << temp << endl;
}

int main() {
    int n_book = 10;
    // Aos(n_book);
    SoA(n_book);
    return 0;
}
