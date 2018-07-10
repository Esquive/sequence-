//
// Created by Eric Falk on 10.07.18.
//


#include "TANSDecoder.h"

TANSDecoder::~TANSDecoder() {
    this->stateTable.clear();
}


//TODO: Parameterize the number of symbols.
void TANSDecoder::readStateTable(uint8_t *symbols) {

    //TODO: Make this a parameter???
    int stateTableSize = (1024 << 1);

    vector<vector<uint16_t>> symbolFrequencyTable;
    symbolFrequencyTable.reserve(256);

    for (int i = 0; i < stateTableSize; i++) {
        symbolFrequencyTable[i].push_back(i + stateTableSize);
    }

    for (uint8_t i = 0; i < symbolFrequencyTable.size(); i++) {
        auto currentState = symbolFrequencyTable[i];
        uint32_t index = 0;
        for (auto it = currentState.begin(); it != currentState.end(); it++, index++) {
            stateTable.insert({*it, StateDecodingTuple{i, index + (uint32_t) currentState.size()}});
        }
    }

    //TODO: Check the allocation of the std libraries. Do I need to delete them?
//    for(auto myVector: symbolFrequencyTable){
//        myVector.clear();
//        myVector.shrink_to_fit();
//    }
//    symbolFrequencyTable.clear();
//    symbolFrequencyTable.shrink_to_fit();

}

void TANSDecoder::decode(const string &srcFile, const string &destFile) {

    //TODO: Make this a parameter???
    int stateTableSize = (1024 << 1);

    //TODO: File Existance checks.
    uint8_t *states = new uint8_t[stateTableSize];


    if (FILE *file = fopen(srcFile.c_str(), "rb")) {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        uint8_t *states = new uint8_t[stateTableSize];
        fread(states, sizeof(uint8_t), stateTableSize, file);

        this->readStateTable(states);

        delete[] states;
        fseek(file, 0, stateTableSize);

        uint8_t *compressedContent = new uint8_t[fileSize - stateTableSize];
        fread(compressedContent, sizeof(uint8_t), fileSize - stateTableSize, file);

//        uint32_t counter = 0;
        vector<uint8_t> uncompressedContent;
        //Entering the decoding loop
        for (int i = 0; i < (fileSize - stateTableSize); i++) {

        }


        cout << "Done reading the state table!" << endl;
    }

}
