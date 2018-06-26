//
// Created by Eric Falk on 26.06.18.
//

#include "../headers/BitOutputStream.h"

BitOutputStream::BitOutputStream(uint8_t* buffer) {
this->buffer = buffer;
}

BitOutputStream::~BitOutputStream() {
    //TODO: Do nothing should be done by the owner of this object
}

void BitOutputStream::writeBit(uint8_t bit) {
    if(bit > 1){
        //TODO: Panic
    }
    currByte = (currByte << 1) | bit;
    bitsWritten++;
    if(bitsWritten == 8){
        buffer[currentBufferPostion] = currByte;
        currByte = 0;
        bitsWritten = 0;
        currentBufferPostion++;
    }
}

uint8_t BitOutputStream::getCurrentBufferPosition() {
    return currentBufferPostion;
}
