#include "bitsequence.h"

void BitSequence::add_bit(bool bit) {
    seq.push_back(bit);
}

size_t BitSequence::get_size() const {
    return seq.size();
}

bool BitSequence::get_bit(size_t i) const {
    return seq[i];
}

BitSequence::BitSequence(const std::vector<bool> &_seq) : seq(_seq) {}

BitSequence BitSequence::operator+ (
    const BitSequence &other
) const {
    std::vector<bool> result;
    result.insert(result.end(), seq.begin(), seq.end());
    result.insert(result.end(), other.seq.begin(), other.seq.end());
    return BitSequence(result);
}

BitSequence& BitSequence::operator+= (
    const BitSequence &other
) {
    seq.insert(seq.end(), other.seq.begin(), other.seq.end());
    return *this;
}

bool BitSequence::operator< (const BitSequence &other) const {
    return seq < other.seq;
}