//
// Created by Eric Falk on 21.08.18.
//

#include "ManberSuffixArray.h"

ManberSuffixArray::ManberSuffixArray(uint8_t *text, uint32_t length): mainSuffix(text,length) {
    index = new uint32_t[length+1];
    rank = new uint32_t[length+1];
    newRank = new uint32_t[length+1];

    // sentinels
    index[length] = length;
    rank[length] = -1;

    

}
