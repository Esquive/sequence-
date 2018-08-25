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
    int64_t* rank;
    uint32_t* newRank;
    unsigned int offset;

    void quicksort(uint32_t* array, int low, int high);
    int partition(uint32_t* array, int low, int high);
    void msd();
    void buildArray();
    inline void swap(uint32_t* array, int first, int second);
    inline bool less(int first, int second);
};


#endif //SEQUENCE_MANBERSUFFIXARRAY_H
