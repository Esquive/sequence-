//
// Created by Eric Falk on 14.07.18.
//

#ifndef SEQUENCE_RANSENCODING_H
#define SEQUENCE_RANSENCODING_H

#include <cstdint>
#include <string>
#include "FrequencyTable.h"

typedef struct SymbolRange {
    uint8_t symbol;
    uint32_t lowerBound;
    uint32_t range;
} SymbolRange;

class RANSEncoder {

private:
    FrequencyTable* frequencyTable;

public:
    RANSEncoder();
    ~RANSEncoder();

    bool encode(const std::string &srcFile, const std::string &destFile);
    bool encode(uint32_t alphabetSize, const std::string &srcFile, const std::string &destFile);
};


#endif //SEQUENCE_RANSENCODING_H
