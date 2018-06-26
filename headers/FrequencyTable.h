//
// Created by Eric Falk on 06.06.18.
//

#ifndef SEQUENCE_FREQUENCYTABLE_H
#define SEQUENCE_FREQUENCYTABLE_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
using namespace std;

typedef struct SymbolCorrectionDeltaTuple {
    uint8_t symbol;
    double delta;

    SymbolCorrectionDeltaTuple() : symbol(0), delta(0.0) {}
    SymbolCorrectionDeltaTuple(uint8_t s, double d) : symbol(s), delta(d) {}


    bool operator<(const SymbolCorrectionDeltaTuple &obj) const {
        return (delta < obj.delta);
    }

} SymbolCorrectionDeltaTuple;

class FrequencyTable {

private:
    uint32_t *frequencies;
    double *symbolProbabilities;
    uint32_t *scaledFrequencies;

    uint32_t total;
    int32_t correction;
    uint32_t scaleTarget;
    uint32_t alphabetSize;

    inline double calculateDelta(double probability, int scaledFrequency, int correctionSign) {
        return probability * log2((double) scaledFrequency / ((double) scaledFrequency + (double) correctionSign));
    };

public:
    FrequencyTable(uint32_t alphabetSize, uint32_t *frequencies, uint32_t total, uint32_t scaleTarget);
    ~FrequencyTable();

    void scale();
    void correctScaling();

    uint32_t * getScaledFrequencies();

    //TODO: Remove function
    int32_t getCorrection();
};

#endif //SEQUENCE_FREQUENCYTABLE_H
