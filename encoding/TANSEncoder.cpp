//
// Created by Eric Falk on 12.06.18.
//


#include "TANSEncoder.h"
#include "../util/ReverseBitReader.h"

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
        outputBuffer = new uint8_t[fileSize];
        bitEncoder = new BitOutputStream(outputBuffer);
        for (int i = fileSize-1 ; i >= 0; i--) {
            encodeSymbol(buffer[i]);
        }
        writeFinalState();
        bitEncoder->flush();

        writeCode(destFile);

        return true;
    } else {
        //TODO: Panic the source file does not exist
        return false;
    }
}

bool TANSEncoder::encodeSymbol(uint8_t byte) {
    SymbolStateEncodingTuple tuple = SymbolStateEncodingTuple{byte, currentState};

    uint8_t currBit = 0;
    while (stateTable.find(tuple) == stateTable.end()) {
        currBit = currentState & 1;
        currentState = currentState >> 1;
        bitEncoder->writeBit(currBit);
        tuple.state = currentState;
    }
    currentState = stateTable[tuple];
    return true;
}

void TANSEncoder::buildStateTable() {

    vector<SymbolStateEncodingTuple> states;
    //TODO: reverse the size of states;

    uint32_t *scaledFrequencies = frequencyTable->getScaledFrequencies();
    for (int i = 0; i < alphabetSize; i++) {
        for (int position = 1; position <= scaledFrequencies[i]; position++) {
            states.push_back(
                    SymbolStateEncodingTuple{(uint8_t) i,
                                             (uint32_t) round(this->m * position / (double) scaledFrequencies[i])}
            );
        }
    }

    stable_sort(states.begin(), states.end());
    uint32_t nextState = 0;

    for (unsigned i = 0; i < states.size(); i++) {
        auto it = states[i];
        it.state = scaledFrequencies[it.symbol];
        stateTable.insert(make_pair(it, (nextState + this->m)));

        scaledFrequencies[it.symbol] += 1;
        nextState += 1;
    }

    //Clean the resources
    states.clear();
    states.shrink_to_fit();
}

void TANSEncoder::writeStateTable(const string &destFile) {

    //Sort the keys
    uint8_t *buffer = new uint8_t[stateTable.size()];


    // Declaring the type of Predicate that accepts 2 pairs and return a bool
    typedef std::function<bool(pair<SymbolStateEncodingTuple, uint>, pair<SymbolStateEncodingTuple, uint>)> Comparator;

    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    Comparator compFunctor =
            [](pair<SymbolStateEncodingTuple, uint> elem1 ,pair<SymbolStateEncodingTuple, uint> elem2)
            {
                    return elem1.second < elem2.second;
            };

    std::vector<pair<SymbolStateEncodingTuple, uint>> keys;
    int size = stateTable.size();

    keys.reserve(stateTable.size());
    for (auto &it : stateTable) {
        keys.push_back(it);
    }

    //TODO: Move the Lambda here
    std::sort(keys.begin(), keys.end(),compFunctor);
    int index = 0;
    for (auto &it : keys) {
        buffer[index] = it.first.symbol;
        index++;
    }

    FILE *pFile = fopen(destFile.c_str(), "wb");
    fwrite(buffer, sizeof(uint8_t), stateTable.size(), pFile);

    //Cleanup
    fclose(pFile);

    delete[] buffer;
    keys.clear();
    keys.shrink_to_fit();
}

void TANSEncoder::writeFinalState() {
    uint32_t iterator = currentState;
    uint8_t val;
    while (iterator != 0) {
        val = iterator & 1;
        bitEncoder->writeBit(val);
        iterator >>= 1;
    }
}

void TANSEncoder::writeCode(const string &destFile) {

    ReverseBitReader* reverseBitReader = new ReverseBitReader(outputBuffer, bitEncoder->getCurrentBufferPosition());
    uint8_t* output = new uint8_t[bitEncoder->getCurrentBufferPosition()];
    BitOutputStream* bitOutput = new BitOutputStream(output);
    int read = -1;
    while((read = reverseBitReader->getNextBit()) != -1){
        bitOutput->writeBit(read);
    }
    bitOutput->flush();
    FILE *pFile = fopen(destFile.c_str(), "ab");
    fwrite(output, sizeof(uint8_t), bitOutput->getCurrentBufferPosition(), pFile);

    //Cleanup
    fclose(pFile);
    delete[] output;
    delete bitOutput;
    delete reverseBitReader;
}
