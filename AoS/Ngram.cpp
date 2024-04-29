#include "Ngram.h"


Ngram::Ngram(string gram) {
    ngram = gram;
    count = 1;
}

Ngram::Ngram(string gram, int n) {
    ngram = gram;
    count = n;
}

void Ngram::add() {
    count = count + 1;
}

void Ngram::add(int n) {
    count = count + n;
}

string Ngram::getNgram() {
    return ngram;
}

int Ngram::getCount() {
    return count;
}
