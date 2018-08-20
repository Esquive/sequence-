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
    void sort(uint32_t low, uint32_t high);

};


#endif //SEQUENCE_SUFFIXARRAY_H
