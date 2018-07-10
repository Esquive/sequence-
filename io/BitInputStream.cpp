//
// Created by Eric Falk on 10.07.18.
//

#include "BitInputStream.h"

BitInputStream::BitInputStream(uint8_t *buffer) {

}

BitInputStream::~BitInputStream() {
    //Do nothing here the buffer is supposed to be deleted from outside. 
}

void BitInputStream::getNextBit() {

}

uint32_t BitInputStream::getCurrentBufferPosition() {
    return 0;
}
