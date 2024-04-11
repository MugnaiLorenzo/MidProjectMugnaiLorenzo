#include "ManageParallel.h"


bool ManageParallel::add_bigram(string gram) {
    for (Ngram *b: bigrams) {
        if (b->getNgram() == gram) {
#pragma omp critical
            b->add();
            return true;
        }
    }
    Ngram *b = new Ngram(gram);
#pragma omp critical
    bigrams.push_back(b);
    return false;

}

bool ManageParallel::add_trigram(string gram) {
    for (Ngram *b: trigrams) {
        if (b->getNgram() == gram) {
            b->add();
            return true;
        }
    }
    Ngram *b = new Ngram(gram);
    trigrams.push_back(b);
    return false;
}

void ManageParallel::printBi() {
    sort(bigrams.begin(), bigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramParallelAoS.png");
    for (int i = 0; i < 30; i++) {
        std::vector<int> x;
        for (int j = 0; j < bigrams[i]->getCount(); j++) {
            x.push_back(i + 1);
            x.push_back(i + 2);
        }
        gnuplot.histogram(x, 2, bigrams[i]->getNgram());
    }
    gnuplot.set_title("");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(0, 30);
    gnuplot.show();
}
