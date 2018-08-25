//
// Created by Eric Falk on 21.08.18.
//

#include <iostream>
#include "ManberSuffixArray.h"

ManberSuffixArray::ManberSuffixArray(uint8_t *text, uint32_t length) : mainSuffix(text, length) {
    index = new uint32_t[length + 1];
    for (int i = 0; i < length; i++) {
        index[i] = i;
    }
    rank = new int64_t[length + 1];
    newRank = new uint32_t[length + 1];

    // sentinels
    index[length] = length;
    rank[length] = -1;

    msd();
    buildArray();

//    for (int i = 0; i < length; i++) {
//        std::cout << std::string((char *) (&text[index[i]]), length - index[i]) << std::endl;
//    }
}

void ManberSuffixArray::msd() {
//    for (int i = 0; i < mainSuffix.length; i++) {
//        rank[i] = mainSuffix[i] - 'a';
//    }
//    quicksort(rank, 0, mainSuffix.length - 1);
    const unsigned int R = 256;

    // calculate frequencies
    unsigned int* freq = new unsigned int[R];
    for (int i = 0; i < mainSuffix.length; i++)
        freq[mainSuffix[i]]++;

    // calculate cumulative frequencies
    unsigned int* cumm = new unsigned int[R];
    for (int i = 1; i < R; i++)
        cumm[i] = cumm[i-1] + freq[i-1];

    // compute ranks
    for (int i = 0; i < mainSuffix.length; i++)
        rank[i] = cumm[mainSuffix[i]];

    // sort by first char
    for (int i = 0; i < mainSuffix.length; i++)
        index[cumm[mainSuffix[i]]++] = i;
}

void ManberSuffixArray::quicksort(uint32_t *array, int low, int high) {
    if (low < high) {
        uint32_t pivot = array[low];
        uint32_t symbol;

        int leftmark = low;
        int rightmark = high;

        int it = leftmark + 1;
        while (it <= rightmark) {
            symbol = array[it];
            if (less(it, pivot)) {
//            if (pivot > symbol) {
//                swap(rank, leftmark, it);
                swap(array, leftmark++, it++);
            } else if (less(pivot,it)) {
//            } else if (pivot < symbol) {
//                swap(rank, it, rightmark);
                swap(array, it, rightmark--);
            } else {
                it++;
            }
        }
        quicksort(array, low, rightmark - 1);
        quicksort(array, rightmark + 1, high);
    }
}

//void ManberSuffixArray::quicksort(uint32_t *array, int low, int high) {
//    if (high <= low) return;
//    int i = partition(array,low, high);
//    quicksort(array,low, i-1);
//    quicksort(array,i+1, high);
//}

int ManberSuffixArray::partition(uint32_t *array, int low, int high) {
    int i = low-1, j = high;
    int v = index[high];

    while (true) {

        // find item on left to swap
        while (less(index[++i], v))
            if (i == high) break;   // redundant

        // find item on right to swap
        while (less(v, index[--j]))
            if (j == low) break;

        // check if pointers cross
        if (i >= j) break;

        swap(array, i, j);
    }

    // swap with partition element
    swap(array, i, high);

    return i;
}

void ManberSuffixArray::buildArray() {
    for (offset = 1; offset < mainSuffix.length; offset += offset) {
        int count = 0;
        for (int i = 1; i <= mainSuffix.length; i++) {
            if (rank[index[i]] == rank[index[i - 1]]) count++;
            else if (count > 0) {
                // sort
                int left = i - 1 - count;
                int right = i - 1;
                quicksort(index, left, right);

                // now fix up ranks
                int r = rank[index[left]];
                for (int j = left + 1; j <= right; j++) {
                    if (less(index[j - 1], index[j])) {
                        r = rank[index[left]] + j - left;
                    }
                    newRank[index[j]] = r;
                }

                // copy back - note can't update rank too eagerly
                for (int j = left + 1; j <= right; j++) {
                    rank[index[j]] = newRank[index[j]];
                }

                count = 0;
            }
        }
    }
}

inline void ManberSuffixArray::swap(uint32_t* array, int first, int second) {
    uint32_t swap = array[first];
    array[first] = array[second];
    array[second] = swap;
}

inline bool ManberSuffixArray::less(int first, int second) {
    return rank[first + offset] < rank[second + offset];
}