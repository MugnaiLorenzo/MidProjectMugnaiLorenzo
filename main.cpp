#include <iostream>
#include "AoS/SequentialAoS.h"
#include "AoS/ParallelAoS.h"
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

void print(vector<double> time1, string title1, vector<double> time2, string title2) {
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/Aos_Parallel_vs_Sequential.png");
    gnuplot.plot(time1, title1);
    gnuplot.plot(time2, title2);
    gnuplot.show();
}

int main() {
    int n_book = 15;
    vector<string> texts;
    load_file(n_book, &texts);
    SequentialAoS *s = new SequentialAoS(texts);
    cout << s->calc_average() << endl;
    s->print();
    ParallelAoS *p = new ParallelAoS(texts);
    cout << p->calc_average() << endl;
    p->print();
    print(p->getTime(), "SequentialAoS", s->getTime(), "ParallelAoS");
    return 0;
}


