//
// Created by Eric Falk on 06.06.18.
//


#include "../headers/FrequencyTable.h"

FrequencyTable::FrequencyTable(uint32_t alphabetSize, uint32_t *frequencies, uint32_t total, uint32_t scaleTarget) {

    this->frequencies = frequencies;
    this->symbolProbabilities = new double[alphabetSize];
    this->scaledFrequencies = new uint32_t[alphabetSize];

    this->total = total;
    this->scaleTarget = scaleTarget;
    this->correction = scaleTarget;
    this->alphabetSize = alphabetSize;
}

FrequencyTable::~FrequencyTable() {
    delete[] frequencies;
    delete[] symbolProbabilities;
    delete[] scaledFrequencies;
}

void FrequencyTable::scale() {

    double scaledFrequency;
    uint32_t scaledDown;
    for (int i = 0; i < alphabetSize; i++) {
        //Scale the symbol frequencies
        scaledFrequency = (double) frequencies[i] * (double) scaleTarget / (double) total;
        scaledDown = (int) scaledFrequency;
        scaledFrequencies[i] = ((scaledFrequency * scaledFrequency) <= (scaledDown * (scaledDown + 1))) ? scaledDown :
                               scaledDown + 1;
        correction -= scaledFrequencies[i];

        //Calculate the symbol probabilities
        symbolProbabilities[i] = (double) frequencies[i] / (double) total;
    }
}

void FrequencyTable::correctScaling() {

    int correctionSign = (correction > 0) ? 1 : -1;
    vector<SymbolCorrectionDeltaTuple> deltas;
    deltas.reserve(alphabetSize);
    double delta;
    for (int i = 0; i < alphabetSize; i++) {
        if (scaledFrequencies[i] > 1) {
//            SymbolCorrectionDeltaTuple tuple = SymbolCorrectionDeltaTuple(i, calculateDelta(symbolProbabilities[i], scaledFrequencies[i], correctionSign));
            deltas.push_back(
                    SymbolCorrectionDeltaTuple(i, calculateDelta(symbolProbabilities[i], scaledFrequencies[i], correctionSign))
            );
        }
    }


    make_heap(deltas.begin(), deltas.end());

    SymbolCorrectionDeltaTuple iter;
    while (correction != 0) {

        iter = deltas.front();
        pop_heap(deltas.begin(), deltas.end());
        deltas.pop_back();
        scaledFrequencies[iter.symbol] += correctionSign;
        correction -= correctionSign;
        //TODO: I guess the probability must be recomputed here
        if (scaledFrequencies[iter.symbol] > 1) {
            iter.delta = calculateDelta(symbolProbabilities[iter.symbol], scaledFrequencies[iter.symbol],
                                         correctionSign);
            deltas.push_back(iter);
            push_heap(deltas.begin(), deltas.end());
        }
    }

    //Cleanup
    deltas.clear();
    deltas.shrink_to_fit();
}

int32_t FrequencyTable::getCorrection() {
    return this->correction;
}

uint32_t *FrequencyTable::getScaledFrequencies() {
    return scaledFrequencies;
}



