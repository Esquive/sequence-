//
// Created by Eric Falk on 18.08.18.
//

#ifndef SEQUENCE_SUFFIXARRAY_H
#define SEQUENCE_SUFFIXARRAY_H


#include "Suffix.h"

class SuffixArray {

public:
    SuffixArray(uint8_t* text, uint32_t length);

private:
    Suffix mainSuffix;
    uint32_t index[6];
    void sort(int low, int high, uint32_t suffixIndex);
    void swap(int first, int second);
};


#endif //SEQUENCE_SUFFIXARRAY_H
