#include "writer.h"

Writer::Writer(const char *output_file) {
    out = std::ofstream(output_file, std::ios::binary);
}

void Writer::flush(size_t leave) {
    while (buffer.size() > leave) {
        unsigned char byte_to_write = 0;
        for (int i = 0; i < 8; i++) {
            byte_to_write *= 2; 
            byte_to_write += buffer.front();
            buffer.pop_front();
        }
        out.write((char*)&byte_to_write, 1);
        bytes_written++;
    } 

}

void Writer::write_byte(unsigned char x) {
    for (int i = 0; i < 8; i++) {
        bool cur_bit = x & (1 << i);
        buffer.push_back(cur_bit);
    }
    flush(); 
}

void Writer::write_int(unsigned int x) {
    for (int i = 0; i < 4; i++) {
        unsigned char cur_byte = x % 256;
        x /= 256;
        write_byte(cur_byte);
    }
    flush();
}

void Writer::write_bits_sequence(const BitSequence &seq) {
    for (size_t i = 0; i < seq.get_size(); i++) {
        buffer.push_back(seq.get_bit(i));
    }
    flush();
}

Writer::~Writer() {
    while (buffer.size() % 8 != 0) {
        buffer.push_back(0);
    }
    flush(0); 
    out.close();
 }

static int up(int x, int y) {
    return x / y + (x % y != 0);
}

 void Writer::encrypt(const char *input_file, const HuffmanTree* tree) {
        write_int(tree->size());
        int table_size = 4;
        int table_bit_size = 0;
        for (unsigned char c : tree->symbols()) {
            write_byte(c);
            table_size++;
            BitSequence seq = tree->get_code(c);
            write_byte(seq.get_size());
            table_size++;
            write_bits_sequence(seq);
            table_bit_size += seq.get_size();
        }
        table_size += up(table_bit_size, 8);
        std::ifstream in = std::ifstream(input_file, std::ios::binary);
        std::cout << tree->total_symbols() << std::endl;
        table_size += 4;
        write_int(tree->total_symbols());
        unsigned char cur_symb;
        while (in) {
            in.read((char*)&cur_symb, 1);
            size_t counted = in.gcount();
            if(!counted) break;
            BitSequence seq = tree->get_code(cur_symb);
            write_bits_sequence(seq);
        }
        while (buffer.size() % 8 != 0) {
            buffer.push_back(0);
        }
        flush(0); 
        std::cout << bytes_written - table_size << std::endl;
        std::cout << table_size << std::endl;
    }
