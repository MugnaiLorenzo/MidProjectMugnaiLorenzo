#include "Ngram.h"

Ngram::Ngram() : ngram(""), count(0) {} // Costruttore predefinito

Ngram::Ngram(std::string gram) : ngram(gram), count(1) {}

Ngram::Ngram(std::string gram, int count) : ngram(gram), count(count) {}

void Ngram::add() {
    count++;
}

void Ngram::add(int n) {
    count += n;
}

std::string Ngram::getNgram() const {
    return ngram;
}

int Ngram::getCount() const {
    return count;
}
