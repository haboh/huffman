#include <iostream>
#include "huffman.h"
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <cstring>

int main(int argc, char *argv[]) {
    bool compress = false;
    bool decompress = false;
    char *input_file = nullptr;
    char *output_file = nullptr;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            compress = true;     
        } 
        if (strcmp(argv[i], "-u") == 0) {
            decompress = true;
        }
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                input_file = argv[i + 1];
            } else {
                throw std::invalid_argument("No input file");
            }
        }
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[i + 1];
            } else {
                throw std::invalid_argument("No output file");
            }
        }
    }

    if ((compress && decompress) || (!compress && !decompress)) {
        throw std::invalid_argument("Multiple or none operation required");
    }
    
    if (!output_file || !input_file) {
        throw std::invalid_argument("No input or output file");
    }

    if (compress) {
        HuffmanArchiver::zip(input_file, output_file);
    } else {
        HuffmanArchiver::unzip(input_file, output_file);
    } 
    return 0; 
}
