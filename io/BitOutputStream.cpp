//
// Created by Eric Falk on 26.06.18.
//

#include "BitOutputStream.h"

BitOutputStream::BitOutputStream(uint8_t *buffer) {
    this->buffer = buffer;
}

BitOutputStream::~BitOutputStream() {
    //TODO: Do nothing should be done by the owner of this object
}

void BitOutputStream::writeBit(uint8_t bit) {
    if (bit > 1) {
        //TODO: Panic
    }
    currByte = (currByte << 1) | bit;
    bitsWritten++;
    if (bitsWritten == 8) {
        buffer[currentBufferPosition] = currByte;
        currByte = 0;
        bitsWritten = 0;
        currentBufferPosition++;
    }
}

uint32_t BitOutputStream::getCurrentBufferPosition() {
    return currentBufferPosition;
}

void BitOutputStream::flush() {
    while(bitsWritten != 0){
        this->writeBit(0);
    }

//    //TODO: maybe decrement the bufferposition again.
//    if (bitsWritten > 0) {
//        buffer[currentBufferPosition] = currByte;
//        //No update to the currentBufferPosition,
//        //we will use this value for the file write.
//        currByte = 0;
//        bitsWritten = 0;
//    }
}

uint32_t BitOutputStream::getBufferSize() {
    return currentBufferPosition - 1;
}
