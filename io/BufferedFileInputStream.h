//
// Created by Eric Falk on 14.07.18.
//

#ifndef SEQUENCE_BUFFEREDFILEINPUTSTREAM_H
#define SEQUENCE_BUFFEREDFILEINPUTSTREAM_H


#include <cstdint>
#include <string>
#include <ntsid.h>

using namespace std;

class BufferedFileInputStream {

public:
    BufferedFileInputStream(const std::string &srcFile):BufferedFileInputStream(srcFile, (1024 << 1)){};
    BufferedFileInputStream(const std::string &srcFile, uint32_t bufferSize);

    int16_t get();
    uint8_t* getSlice(uint32_t begin);

    ~BufferedFileInputStream();

private:

    uint8_t* buffer;
    uint32_t capacity;
    uint32_t position;

    bool hasRemaining(uint32_t number);
};


#endif //SEQUENCE_BUFFEREDFILEINPUTSTREAM_H
