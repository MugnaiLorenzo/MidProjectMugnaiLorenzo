#include "Manage.h"


bool Manage::add_bigram(string gram) {
    for (Ngram *b: bigrams) {
        if (b->getNgram() == gram) {
            b->add();
            return true;
        }
    }
    Ngram *b = new Ngram(gram);
    bigrams.push_back(b);
    return false;

}

bool Manage::add_trigram(string gram) {
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

void Manage::printBi() {
    sort(bigrams.begin(), bigrams.end(), [](Ngram *a, Ngram *b) {
        return (a->getCount() > b->getCount());
    });
    Gnuplot gnuplot{};
    gnuplot.redirect_to_png("./../Image/AoS/HistogramSequentialAoS.png");
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
