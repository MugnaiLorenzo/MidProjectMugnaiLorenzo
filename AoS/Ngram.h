#ifndef NGRAM_H
#define NGRAM_H

#include <string>

class Ngram {
public:
    Ngram(); // Costruttore predefinito
    Ngram(std::string gram);
    Ngram(std::string gram, int count);

    void add();
    void add(int n);

    std::string getNgram() const;
    int getCount() const;

private:
    std::string ngram;
    int count;
};

#endif // NGRAM_H
