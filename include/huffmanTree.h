#pragma once 

#include <set>
#include <exception>
#include <map>
#include <vector>
#include <iostream>
#include "bitsequence.h"

class HuffmanTree {
private:
    struct HuffmanTreeNode {
        std::set<unsigned char> letters;
        size_t size;
        HuffmanTreeNode *zero_link;
        HuffmanTreeNode *one_link;
        static HuffmanTreeNode* merge_two_nodes(HuffmanTreeNode *a, HuffmanTreeNode *b);
        ~HuffmanTreeNode();
    };
    struct HuffmanTreeNodeCmp {
        bool operator()(const HuffmanTreeNode *n1, const HuffmanTreeNode *n2) const;
    };
    HuffmanTreeNode *root;
public:
    HuffmanTree(const std::map<unsigned char, size_t> &symbol_occurences);
    ~HuffmanTree();

    BitSequence get_code(unsigned char c) const;
    size_t size() const;
    size_t total_symbols() const;
    std::set<unsigned char> symbols() const;

    class SymbolAbsentException : public std::logic_error {
    public:
        SymbolAbsentException(std::string message) : std::logic_error(message) {}
    };
};