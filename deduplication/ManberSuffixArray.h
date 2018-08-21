//
// Created by Eric Falk on 21.08.18.
//

#ifndef SEQUENCE_MANBERSUFFIXARRAY_H
#define SEQUENCE_MANBERSUFFIXARRAY_H


#include <cstdint>
#include "Suffix.h"

class ManberSuffixArray {

public:
    ManberSuffixArray(uint8_t* text, uint32_t length);

private:

    Suffix mainSuffix;
    uint32_t* index;
    uint32_t* rank;
    uint32_t* newRank;

    void sort(int low, int high, uint32_t suffixIndex);
    void swap(int first, int second);

};


#endif //SEQUENCE_MANBERSUFFIXARRAY_H
