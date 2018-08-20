//
// Created by Eric Falk on 18.08.18.
//

#include <cstdint>
#include "SuffixArray.h"
#include "Suffix.h"

SuffixArray::SuffixArray(uint8_t* text, uint32_t length) {

    mainSuffix = Suffix(text, length);
    uint32_t* index = new uint32_t[length];
    for(int i=0;i<length;i++){
        index[i] = i;
    }



}


void SuffixArray::sort(uint32_t low, uint32_t high) {
    int pivotIndex = low;

    int leftmark = low + 1;
    int rightmark = high;
    for(int i = low+1; i<high; i++){
        if(mainSuffix[leftmark] < mainSuffix[pivotIndex]) {
            //TODO: Swap
        } else if (mainSuffix[leftmark] )
    }

}
