//
// Created by Eric Falk on 06.06.18.
//

#ifndef SEQUENCE_FREQUENCYTABLE_H
#define SEQUENCE_FREQUENCYTABLE_H

#include <cstdint>
using namespace std;

class FrequencyTable {

private:
    uint32_t *frequencies;
    uint32_t total;

public:
    FrequencyTable(uint32_t* frequencies, uint32_t total);
    ~FrequencyTable();

    uint32_t* scale(uint32_t scaleTarget);
    void correctScaling();
};

#endif //SEQUENCE_FREQUENCYTABLE_H
