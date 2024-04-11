#include <iostream>
#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
#include "SoA/SequentialSoA.h"
#include "SoA/ParallelSoA.h"
#include "include/gplot++.h"

void load_file(int n, vector<string> *texts) {
    string title;
    for (int i = 0; i < n; i++) {
        title = "./../Testi/book" + to_string(i) + ".txt";
        string text;
        ifstream newfile;
        newfile.open(title, ios::in);
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

void print(vector<double> time1, string title1, vector<double> time2, string title2, string file) {
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png(file);
    gnuplot.plot(time1, title1);
    gnuplot.plot(time2, title2);
    gnuplot.show();
}

void printAverage(SequentialAoS *s, ParallelAoS *p, SequentialSoA *sSoA, ParallelSoA *pSoA) {
    string temp = "";
    temp += "Tempo medio operazione bigrammi Sequenziale AoS: " + to_string(s->calc_average())+"\n";
    temp += "Tempo medio operazione bigrammi Parallelo AoS: " + to_string(p->calc_average())+"\n";
    temp += "Tempo medio operazione bigrammi Sequenziale SoA: " + to_string(sSoA->calc_average_bi())+"\n";
    temp += "Tempo medio operazione bigrammi Parallelo SoA: " + to_string(pSoA->calc_average_bi())+"\n";
    temp += "Tempo medio operazione trigrammi Sequenziale SoA: " + to_string(sSoA->calc_average_tri())+"\n";
    temp += "Tempo medio operazione trigrammi Parallelo SoA: " + to_string(pSoA->calc_average_tri());
    cout << temp << endl;
}

int main() {
    int n_book = 15;
    vector<string> texts;
    load_file(n_book, &texts);
    SequentialAoS *s = new SequentialAoS(texts);
    s->print();
    ParallelAoS *p = new ParallelAoS(texts);
    p->print();
    print(p->getTime(), "SequentialAoS", s->getTime(), "ParallelAoS", "./../Image/AoS/Aos_Parallel_vs_Sequential.png");
    SequentialSoA *sSoA = new SequentialSoA(texts);
    sSoA->print_bi();
    sSoA->print_tri();
    ParallelSoA *pSoA = new ParallelSoA(texts);
    pSoA->print_bi();
    pSoA->print_tri();
    print(sSoA->getTime_bi(), "SequentialSoA", pSoA->getTime_bi(), "ParallelSoA",
          "./../Image/SoA/SoA_Parallel_vs_Sequential_Bi.png");
    print(sSoA->getTime_tri(), "SequentialSoA", pSoA->getTime_tri(), "ParallelSoA",
          "./../Image/SoA/SoA_Parallel_vs_Sequential_Tri.png");
    printAverage(s, p, sSoA, pSoA);
    return 0;
}
