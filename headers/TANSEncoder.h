//
// Created by Eric Falk on 12.06.18.
//

#ifndef SEQUENCE_TANSENCODER_H
#define SEQUENCE_TANSENCODER_H


//#include <tclDecls.h>
#include <unordered_map>
#include "FrequencyTable.h"
#include "BitOutputStream.h"
using namespace std;

typedef struct SymbolStateEncodingTuple{
    uint8_t symbol;
    uint32_t state;

    bool operator<(const SymbolStateEncodingTuple &obj) const {
        return (state < obj.state);
    }

    bool operator==(const SymbolStateEncodingTuple &obj) const {
        return (symbol == obj.symbol && state == obj.state);
    }
} SymbolStateEncodingTuple;

//Adding a hash function for the above struct
namespace std
{
    template <>
    struct hash<SymbolStateEncodingTuple>
    {
        size_t operator()(const SymbolStateEncodingTuple& obj) const
        {
            size_t part1 = hash<uint8_t>{}(obj.symbol);
            size_t part2 = hash<uint>{}(obj.state);
            return part1 ^ (part2 << 1);
        }
    };
}


class TANSEncoder {
private:
    FrequencyTable *frequencyTable;
    uint32_t currentState;
    uint32_t alphabetSize;

    uint32_t m;
    uint32_t precision;

    unordered_map<SymbolStateEncodingTuple, uint> stateTable;
    uint8_t* outputBuffer;
    BitOutputStream* bitEncoder;


    void buildStateTable();
    void writeFinalState();
    void writeStateTable(const string &destFile);


public:
    TANSEncoder(){};
    ~TANSEncoder();

    inline bool encodeSymbol(uint8_t byte);
    bool encode(const string& srcFile, const string& destFile);
    bool encode(uint alphabetSize, const string& srcFile, const string& destFile);
};


#endif //SEQUENCE_TANSENCODER_H
