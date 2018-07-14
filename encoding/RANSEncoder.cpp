//
// Created by Eric Falk on 14.07.18.
//

#include "RANSEncoder.h"

RANSEncoder::RANSEncoder() {

}

RANSEncoder::~RANSEncoder() {
    delete FrequencyTable;
}

bool RANSEncoder::encode(const std::string &srcFile, const std::string &destFile) {
    return encode(256,srcFile,destFile);
}

bool RANSEncoder::encode(uint32_t alphabetSize, const std::string &srcFile, const std::string &destFile) {
    return false;
}
