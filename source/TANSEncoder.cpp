//
// Created by Eric Falk on 12.06.18.
//


#include "../headers/TANSEncoder.h"

TANSEncoder::~TANSEncoder() {
    delete this->frequencyTable;
    delete this->bitEncoder;
    delete this->outputBuffer;
    stateTable.clear();
}

bool TANSEncoder::encode(const string &srcFile, const string &destFile) {
    TANSEncoder::encode(256, srcFile, destFile);
}

bool TANSEncoder::encode(uint alphabetSize, const string &srcFile, const string &destFile) {

    this->alphabetSize = alphabetSize;
    this->precision = (int) floor(log2(alphabetSize)) + 3;
    this->m = 1 << precision;
    this->currentState = (m << 1) - 1;


    //TODO: Remove the hardcoded file name.
    if (FILE *file = fopen("book1", "rb")) {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        //TODO: Implement a buffered Reader reading the file chunk by chunk.
        uint8_t *buffer = new uint8_t[fileSize];
        uint32_t *frequencies = new uint32_t[alphabetSize];

        fread(buffer, sizeof(uint8_t), fileSize, file);
        fclose(file);

        uint32_t total = 0;
        for (int i = 0; i < fileSize; i++) {
            frequencies[buffer[i]]++;
            total++;
        }

        //TODO: Compute the scaleTarget.
        frequencyTable = new FrequencyTable(alphabetSize, frequencies, total, 2048);
        frequencyTable->scale();
        frequencyTable->correctScaling();

        this->buildStateTable();
        this->writeStateTable(destFile);


        //TODO: Get a better approximation and create an ouputStream that handle buffer overflows
        outputBuffer = new uint8_t[fileSize / 2];
        bitEncoder = new BitOutputStream(outputBuffer);
        for (int i = 0; i < fileSize; i++) {
            encodeSymbol(buffer[i]);
//                    cout << unsigned(buffer[i]);
        }
        return true;
    } else {
        //TODO: Panic the source file does not exist
        return false;
    }
}

bool TANSEncoder::encodeSymbol(uint8_t byte) {
    SymbolStateEncodingTuple tuple = SymbolStateEncodingTuple{byte, currentState};

    for (pair<SymbolStateEncodingTuple, uint> element : stateTable) {
        cout << element.first.symbol << " :: " << element.first.state << " :: "<< element.second << std::endl;
    }

//    cout << "Symbol: " << unsigned(byte) << " State: " << currentState << endl;
    uint8_t currBit = 0;


//    unordered_map<SymbolStateEncodingTuple, uint>::iterator it = stateTable.find(tuple);
//
    while ( stateTable.find(tuple) == stateTable.end()) {
        currBit = currentState & 1;
        currentState = currentState >> 1;
        bitEncoder->writeBit(currBit);
        tuple.state = currentState;
    }
//    stateTable[currentState];
//
    bool found = (stateTable.find(tuple) == stateTable.end());
    currentState = stateTable[ tuple ];
    return true;
}

void TANSEncoder::buildStateTable() {

    vector<SymbolStateEncodingTuple> states;
    vector<SymbolStateEncodingTuple>::iterator it;
    //TODO: reverse the size of states;

    uint32_t *scaledFrequencies = frequencyTable->getScaledFrequencies();
    for (int i = 0; i < alphabetSize; i++) {
        for (int position = 1; position <= scaledFrequencies[i]; position++) {
            states.push_back(
                    SymbolStateEncodingTuple{(uint8_t) i,
                                             (uint) round(this->m * position / (double) scaledFrequencies[i])}
            );
        }
    }

    make_heap(states.begin(), states.end());
    uint nextState = 0;

    for (it = states.begin(); it != states.end(); it++) {
        uint8_t symbol = (*it).symbol;
        uint state = (*it).state;
        (*it).state = scaledFrequencies[(*it).symbol];
        stateTable.insert(make_pair(*it, (nextState + this->m)));

        scaledFrequencies[(*it).symbol] += 1;
        nextState += 1;
    }

    //Clean the resources
    states.clear();
    states.shrink_to_fit();
}

void TANSEncoder::writeStateTable(const string &destFile) {

    //Sort the keys
    uint8_t *buffer = new uint8_t[stateTable.size()];

//    uint8_t* buffer2 = (uint8_t *)malloc(stateTable.size()*sizeof(uint8_t));
    std::vector<SymbolStateEncodingTuple> keys;

    int size = stateTable.size();

    keys.reserve(stateTable.size());
    for (auto &it : stateTable) {
        keys.push_back(it.first);
    }

    std::sort(keys.begin(), keys.end());
    int index = 0;
    for (auto &it : keys) {
        buffer[index] = it.symbol;
    }

    FILE *pFile = fopen(destFile.c_str(), "wb");
    fwrite(buffer, sizeof(uint8_t), stateTable.size(), pFile);

    //Cleanup
    fclose(pFile);

    delete[] buffer;
    keys.clear();
    keys.shrink_to_fit();
}
