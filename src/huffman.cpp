#include "huffman.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

namespace HuffmanArchiver {
    static inline std::map<unsigned char, size_t> count_symbols_occurence(
        const char *input_file) {

        static const size_t buff_size = 1024;
        static unsigned char temp_buffer[buff_size];

        std::ifstream in = std::ifstream(input_file);
        std::map<unsigned char, size_t> count_symbols;
        while (true) {
            in.read((char*)temp_buffer, buff_size);
            size_t counted = in.gcount();
            if(!counted) break;
            for (size_t i = 0; i < counted; i++) {
                count_symbols[temp_buffer[i]]++;
            }
        }

        return count_symbols;
    }

    void zip(const char *input_file, const char *output_file) {
        auto count_symbols = count_symbols_occurence(input_file);
        HuffmanTree* tree = new HuffmanTree(count_symbols);
        Writer writer(output_file);
        writer.encrypt(input_file, tree);
        delete tree;
    }

    void unzip(const char *input_file, const char *output_file) {
        Reader reader(input_file);
        reader.decrypt(output_file);
    }
}
