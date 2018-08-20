////
//// Created by Eric Falk on 14.07.18.
////
//
//#include "RANSEncoder.h"
//
//RANSEncoder::RANSEncoder() {
//
//}
//
//RANSEncoder::~RANSEncoder() {
//    delete this->frequencyTable;
//}
//
//bool RANSEncoder::encode(const std::string &srcFile, const std::string &destFile) {
//    return encode(256,srcFile,destFile);
//}
//
//bool RANSEncoder::encode(uint32_t alphabetSize, const std::string &srcFile, const std::string &destFile) {
//
//    this->alphabetSize = alphabetSize;
//    this->precision = (int) floor(log2(alphabetSize)) + 3;
//    this->m = 1 << precision;
//    this->currentState = (m << 1) - 1;
//
//
//    if (FILE *file = fopen(srcFile.c_str(), "rb")) {
//        fseek(file, 0, SEEK_END);
//        size_t fileSize = ftell(file);
//        fseek(file, 0, SEEK_SET);
//
//        //TODO: Implement a buffered Reader reading the file chunk by chunk.
//        uint8_t *buffer = new uint8_t[fileSize];
//        uint32_t *frequencies = new uint32_t[alphabetSize];
//
//        fread(buffer, sizeof(uint8_t), fileSize, file);
//        fclose(file);
//
//        uint32_t total = 0;
//        for (int i = 0; i < fileSize; i++) {
//            frequencies[buffer[i]]++;
//            total++;
//        }
//
//        //TODO: Compute the scaleTarget.
//        frequencyTable = new FrequencyTable(alphabetSize, frequencies, total, 2048);
//        frequencyTable->scale();
//        frequencyTable->correctScaling();
//
//        return true;
//    } else {
//        //TODO: Panic the source file does not exist
//        return false;
//    }
//
//    return false;
//}
