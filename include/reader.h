#pragma once 

#include <iostream>
#include <fstream>
#include <queue>
#include "huffmanTree.h"
#include <algorithm>

class Reader {
public:
    Reader(const char *input_file);
    void decrypt(const char *output_file);
private:
    std::ifstream in;

    static const int MAX_BIT_BUFFER_SIZE = 8192;
    static const int BYTE_BUFFER_SIZE = 1024;
    unsigned char temp_buffer[BYTE_BUFFER_SIZE];
    std::deque<bool> buffer;
    
    unsigned char read_byte();
    unsigned int read_int();
    bool read_bit();  
    BitSequence read_bits_sequence(int len);
    void fill_buffer();
    int bytes_read = 0;
};
