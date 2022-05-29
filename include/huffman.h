#pragma once 

#include <map>
#include <set>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <iostream>
#include "huffmanTree.h"
#include "writer.h"
#include "reader.h"

/* 
ENCRYPTED FILE FORMAT

Header:
[4 byte] table size (unsigned int)

repeat(table_size)
-> [1 byte] symbol(char)
-> [1 byte] code_length (unsinged char)
-> [code_length bits] {010101} code

Content:
[4 byte] text size (unsigned int)
[text_size]  bits sequences 

Padding:
Up to ceil amount of bytes (i.e. it could be complementary zeros at the end)
*/


namespace HuffmanArchiver {
    void zip(const char *input_file, const char *output_file);
    void unzip(const char *input_file, const char *output_file);
};
