//
// Created by Eric Falk on 18.08.18.
//

#ifndef SEQUENCE_SUFFIX_H
#define SEQUENCE_SUFFIX_H

#include <cstdint>

class Suffix {

//private:


public:
    uint8_t *sequence;
    uint32_t length;

    Suffix(uint8_t *sequence, uint32_t length): sequence(sequence), length(length) {

    }

    virtual ~Suffix() {
        //We do nothing the array must be destroyed by the main thread;
    }

    inline uint8_t &operator[](int i) {
        return sequence[i];
    }
};

#endif //SEQUENCE_SUFFIX_H
