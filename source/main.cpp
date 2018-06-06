

#include <cstdio>
#include <cstdint>
#include <iostream>
#include "../headers/FrequencyTable.h"

int main() {

//    ifstream inStream;
//    inStream.open("book1",std::ios::binary);
//    uint8_t x;
//
//    if(!inStream){
//        cerr << "Error while opening the file!";
//        exit(1);
//    }
//
//    char c = inStream.get();
//
//    while (inStream.good()) {
//        std::cout << c;
//        c = inStream.get();
//    }
//
//    while(inStream >> x) {
//        cout << "value is " << unsigned(x) << endl;
//    }
//
//    std::cout << "Hello, World!" << std::endl;
//

    FILE *file = fopen("book1", "rb");

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = new uint8_t[fileSize];
    uint32_t *frequencies = new uint32_t[256];

    fread(buffer, sizeof(uint8_t), fileSize, file);
    fclose(file);

    uint32_t total = 0;
    for (int i = 0; i < fileSize; i++) {
        std::cout << unsigned(buffer[i]) << std::endl;
        frequencies[buffer[i]]++;
        total++;
    }

    FrequencyTable frequencyTable = FrequencyTable(frequencies, total);
    uint32_t *scaledFrequencies = frequencyTable.scale(2048);


    std::cout << "done" << std::endl;

    //count the frequencies

//    long lSize;
//    char * buffer;
//    size_t result;
//
//    buffer = (char*) malloc (sizeof(char)*lSize);
//    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
//
//    // copy the file into the buffer:
//    result = fread (buffer,1,lSize,file);
//    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
//
//    sizeof(char)*lSize;
//    for(int i =0; i < sizeof(char)*lSize; i++){
//        std::cout << *(buffer+i) << std::endl;
//    }

    return 0;
}