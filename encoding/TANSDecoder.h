//
// Created by Eric Falk on 10.07.18.
//

#ifndef SEQUENCE_TANSDECODER_H
#define SEQUENCE_TANSDECODER_H


#include <cstdint>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef struct StateDecodingTuple{
    uint8_t symbol;
    uint32_t previousState;
} StateDecodingTuple;


class TANSDecoder {
private:
    unordered_map<uint16_t, StateDecodingTuple> stateTable;
    void readStateTable(uint8_t* states);

public:
    TANSDecoder(){};
    ~TANSDecoder();

    void decode(const std::string &srcFile, const std::string &destFile);
};


#endif //SEQUENCE_TANSDECODER_H
