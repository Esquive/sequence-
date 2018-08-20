//
// Created by Eric Falk on 18.08.18.
//

#ifndef SEQUENCE_SUFFIX_H
#define SEQUENCE_SUFFIX_H

#include <cstdint>

class Suffix {

    private:
    uint8_t *sequence;
    uint32_t length;

public:
    Suffix(uint8_t *sequence, uint32_t length) : sequence(sequence), length(length) { }
    virtual ~Suffix() {
        //We do nothing the array must be destroyed by the main thread;
    }

    uint8_t operator [](int i) const    {return sequence[i];}
    uint8_t & operator [](int i) {return sequence[i];}
};

#endif //SEQUENCE_SUFFIX_H
