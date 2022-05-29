#pragma once 
#include "huffmanTree.h"
#include <fstream>
#include <iostream>

class Writer {
public:
    Writer(const char *output_file);
    ~Writer(); 
    void encrypt(const char *input_file, const HuffmanTree *tree);
private:
    std::ofstream out; 
    static const size_t MAX_BUFFER_SIZE = 1024;

    std::deque<bool> buffer;
    void flush(size_t leave = MAX_BUFFER_SIZE); 
    void write_byte(unsigned char x);
    void write_int(unsigned int x);
    void write_bits_sequence(const BitSequence &seq);
    int bytes_written = 0;
};
