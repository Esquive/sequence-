//
// Created by Eric Falk on 18.08.18.
//

#include <cstdint>
#include <iostream>
#include "SuffixArray.h"
#include "Suffix.h"

using namespace std;

SuffixArray::SuffixArray(uint8_t *text, uint32_t length) : mainSuffix(text, length) {
    for (int i = 0; i < length; i++) {
        index[i] = i;
    }
    sort(0, length - 1, 0);

    for (int i = 0; i < length; i++) {
        std::cout << std::string( (char*)(&text[index[i]]), length - index[i] ) << std::endl;
    }
}


void SuffixArray::sort(int low, int high, uint32_t suffixIndex) {

    if (low < high) {
        uint32_t lastIndex = index[low] + suffixIndex;
        uint8_t pivot = mainSuffix[index[low] + suffixIndex];
        uint8_t symbol;

        int leftmark = low;
        int rightmark = high;

        int it = leftmark + 1;
        while (it <= rightmark) {
            symbol = mainSuffix[index[it] + suffixIndex];
            if (pivot > symbol) {
                swap(leftmark++, it++);
            } else if (pivot < symbol) {
                swap(it, rightmark--);
            } else {
                it++;
            }
        }

        sort(low, leftmark - 1, suffixIndex);
        if (lastIndex < mainSuffix.length) sort(leftmark, rightmark, suffixIndex + 1);
        sort(rightmark + 1, high, suffixIndex);
    }

}

void SuffixArray::swap(int first, int second) {
    uint32_t swap = index[first];
    index[first] = index[second];
    index[second] = swap;
}
