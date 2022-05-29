#include "reader.h"

Reader::Reader(const char *input_file) {
    in = std::ifstream(input_file, std::ios::binary);
}

unsigned char Reader::read_byte() {
    fill_buffer();
    unsigned char result = 0;
    for (int i = 0; i < 8; i++) {
        result *= 2;
        result += buffer[7 - i];
    }
    for (int i = 0; i < 8; i++) {
        buffer.pop_front();
    }
    return result;
}

unsigned int Reader::read_int() {
    unsigned int result = 0;
    std::vector<unsigned char> bb = {
        read_byte(),
        read_byte(),
        read_byte(),
        read_byte()
    };
    for (int i = 0; i < 4; i++) {
        result *= 256;
        result += bb[3 - i];
    }
    return result;
}

bool Reader::read_bit() {
    fill_buffer();
    bool result = buffer.front();
    buffer.pop_front();
    return result;
}

BitSequence Reader::read_bits_sequence(int len) {
    fill_buffer();
    BitSequence result;
    for (int i = 0; i < len; i++) {
        result.add_bit(buffer.front());
        buffer.pop_front();
    }
    return result;
}

void Reader::fill_buffer() {
    while (buffer.size() < MAX_BIT_BUFFER_SIZE) {
        in.read((char*)temp_buffer, BYTE_BUFFER_SIZE);
        size_t counted = in.gcount();
        if(!counted) break;
        bytes_read += counted;
        for (size_t byte_index = 0; byte_index < counted; byte_index++) {
            for (int i = 7; i >= 0; i--) {
                bool cur_bit = temp_buffer[byte_index] & (1 << i);
                buffer.push_back(cur_bit);
            }
        }
    }
}

static int up(int x, int y) {
    return x / y + (x % y != 0);
}


void Reader::decrypt(const char *output_file) {

    int compressed_size = 0;
    int table = 8;
    int table_bit_size = 0;
    int unzipped_size = 0;
    size_t table_size = read_int();

    std::map<BitSequence, unsigned char> dict;
    for (size_t i = 0; i < table_size; i++) {
        unsigned char symb = read_byte();
        unsigned char len = read_byte();
        BitSequence seq = read_bits_sequence(len);
        table += 2;
        table_bit_size += len;
        dict[seq] = symb;
    }
    table += up(table_bit_size, 8);
    std::ofstream out = std::ofstream(output_file, std::ios::binary);
    size_t text_size = read_int();
    unzipped_size = text_size;

    for (size_t i = 0; i < text_size; i++) {
        BitSequence cur_seq; 
        while (dict.count(cur_seq) == 0) {
            compressed_size++;
            cur_seq.add_bit(read_bit()); 
        }
        out.write((char*)&dict[cur_seq], 1);
    }

    std::cout << bytes_read - table << std::endl;
    std::cout << unzipped_size << std::endl;
    std::cout << table << std::endl;
}

