#pragma once 

#include <vector>
#include <queue>
class BitSequence {
private:
    std::vector<bool> seq;
    BitSequence(const std::vector<bool> &_seq);
public:
    BitSequence() = default;
    void add_bit(bool bit);
    size_t get_size() const;
    bool get_bit(size_t i) const;
    BitSequence operator+ (const BitSequence &other) const;     
    BitSequence& operator+= (const BitSequence &other);     
    bool operator< (const BitSequence &other) const;
};