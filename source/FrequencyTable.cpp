//
// Created by Eric Falk on 06.06.18.
//

#include <cstdio>
#include <cstdlib>
#include "../headers/FrequencyTable.h"

FrequencyTable::FrequencyTable(uint32_t *frequencies, uint32_t total) {
    this->frequencies = frequencies;
    this->total = total;
}

FrequencyTable::~FrequencyTable() {
    delete [] frequencies;
    free(&total);
}

uint32_t* FrequencyTable::scale(uint32_t scaleTarget) {

    size_t arraySize = 256;
    uint32_t *scaledFrequencies = new uint32_t[arraySize];

    for(int i = 0; i<arraySize; i++){
        scaledFrequencies[i] = frequencies[i] * scaleTarget / total;
    }
}



