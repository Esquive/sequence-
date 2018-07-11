//
// Created by Eric Falk on 10.07.18.
//

#include "BitInputStream.h"

BitInputStream::BitInputStream(uint8_t *buffer, uint32_t bufferSize) {
    this->buffer = buffer;
    this->currentBufferPosition = 0;
    this->bufferSize = bufferSize;
    this->bitsRemaining = 0;
}

BitInputStream::~BitInputStream() {
    //Do nothing here the buffer is supposed to be deleted from outside.
}

int8_t BitInputStream::getNextBit() {
    if(bitsRemaining ==0){
        if(hasRemaining()){
            this->currByte = buffer[currentBufferPosition];
            currentBufferPosition++;
            bitsRemaining = 8;
        } else {
            return -1;
        }
    }
    return (currByte >> --bitsRemaining) & 1;
}

uint32_t BitInputStream::getCurrentBufferPosition() {

}

bool BitInputStream::hasRemaining() {
    return currentBufferPosition < bufferSize;
}
