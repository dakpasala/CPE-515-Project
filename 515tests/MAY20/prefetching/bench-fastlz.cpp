#include <iostream>
#include <vector>
#include <cstdint>

extern "C" {
    #include "fastlz.h"
}

constexpr size_t DATA_SIZE = 1 << 22;  

int main() {
    std::vector<unsigned char> input(DATA_SIZE);
    
    uint32_t state = 12345;
    for (size_t i = 0; i < DATA_SIZE; i++) {
        state = state * 1103515245 + 12345;
        unsigned char byte = (unsigned char)((state >> 16) & 0xFF);
        
        byte = 32 + (byte % 95);
        
        input[i] = byte;
    }
    
    const char* common[] = {
        " the ", " and ", " of ", " to ", " is ", " in "
    };
    for (size_t i = 0; i < DATA_SIZE - 8; i += 100) {
        const char* word = common[i % 6];
        size_t wlen = 5;  // each common phrase is 5 chars
        for (size_t j = 0; j < wlen && i + j < DATA_SIZE; j++) {
            input[i + j] = (unsigned char)word[j];
        }
    }

    std::vector<unsigned char> output(DATA_SIZE + DATA_SIZE / 20 + 66);

    int compressed = fastlz_compress_level(1, input.data(), DATA_SIZE, output.data());
    return 0;
}
