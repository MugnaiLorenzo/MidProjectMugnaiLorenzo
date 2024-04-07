#include "Ngram.h"


Ngram::Ngram(string gram) {
    ngram = gram;
    count = 1;
}

void Ngram::add() {
    count = count + 1;
}

string Ngram::getNgram() {
    return ngram;
}

int Ngram::getCount() {
    return count;
}
