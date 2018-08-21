#include <cstdint>
#include "encoding/FrequencyTable.h"
#include "encoding/TANSEncoder.h"
#include "encoding/TANSDecoder.h"
#include "util/ReverseBitReader.h"
#include "deduplication/SuffixArray.h"

int main() {

    //TODO: TEST the Encoder

//    clock_t tStart = clock();
//    /* Do your stuff here */
//
//    TANSEncoder* encoder = new TANSEncoder();
//    encoder->encode("book1","book1cpp.tans");
//    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


//    TANSDecoder* decoder = new TANSDecoder();
//    decoder->decode("book1cpp.tans", "book1uncomp");

    //TODO: Test the reverse BitStream

    //1010 1010
    //1111 0000
    //0000 1111
    //1000 1101
//    uint8_t values[] = {170,240,15,141};
//    ReverseBitReader* reader = new ReverseBitReader(values, 4);
//
//
//    int read = 0;
//    int counter = 0;
//    while( (read = reader->getNextBit()) != -1){
//        cout << unsigned(read);
//        counter++;
//        if(counter == 4){
//            cout << " ";
//        } else if (counter == 8) {
//            cout << endl;
//            counter = 0;
//        }
//
//    }










//    uint32_t value = 1;
//    void* pointer = (void*)&value;
//    uint8_t * buffer = (uint8_t*)pointer;
//    for (int i = 0; i < 4; i++) {
//        cout << unsigned(buffer[i]) << endl;
////        if (i == 0) {
////            for (int j = 0; j < 8; j++) {
////                cout << (buffer[i] << j) << endl;
////            }
////        }
//    }

    auto name = std::string("This is a bananasplit");
    SuffixArray* array = new SuffixArray( (uint8_t*)name.c_str(), name.length());


//    uint8_t* buffer = new uint8_t[8];
//    buffer[0] = 1;
//    buffer[1] = 0;
//    buffer[2] = 0;
//    buffer[3] = 0;
//
//    buffer[4] = 0;
//    buffer[5] = 0;
//    buffer[6] = 0;
//    buffer[7] = 2;
//
//
//    uint32_t* value2 = (uint32_t*)(buffer);
//    uint32_t swap = __builtin_bswap32(*value2);
//    cout << *value2 << endl;
//    cout << swap << endl;
//
//    swap = __builtin_bswap32(value2[1]);
//    cout << *(value2 +1) << endl;
//    cout << swap << endl;
//
//    for(int i = 0; i < 8 ; i++){
//        int val = buffer[0] & (128 >> i);
//////        buffer[0] = buffer[0] >> 1;
//        cout << val << endl;
//    }
//
//
//    for(int i = 0; i < 8 ; i++){
////        int val = buffer[0] & (0x08 >> i);
//
//        cout << (0x80 >> i) << endl;
//    }
//
//    uint32_t* val = new uint32_t(1);
//    for(int i = 0; i < 8; i++){
//        cout << (*val << i) << endl;
//    }

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

//    FILE *file = fopen("book1", "rb");
//
//    fseek(file, 0, SEEK_END);
//    size_t fileSize = ftell(file);
//    fseek(file, 0, SEEK_SET);
//
//    uint8_t *buffer = new uint8_t[fileSize];
//    uint32_t *frequencies = new uint32_t[256];
//
//    fread(buffer, sizeof(uint8_t), fileSize, file);
//    fclose(file);
//
//    uint32_t total = 0;
//    for (int i = 0; i < fileSize; i++) {
////        std::cout << unsigned(buffer[i]) << std::endl;
//        frequencies[buffer[i]]++;
//        total++;
//    }
//
//    FrequencyTable frequencyTable = FrequencyTable(256, frequencies, total, 2048);
//    frequencyTable.scale();
//    uint32_t correction = frequencyTable.getCorrection();
//    frequencyTable.correctScaling();
//
//
//    std::cout << "done" << std::endl;

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