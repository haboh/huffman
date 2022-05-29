#include "huffmanTree.h"

bool HuffmanTree::HuffmanTreeNodeCmp::operator()(
    const HuffmanTreeNode *n1, 
    const HuffmanTreeNode *n2) const {
    return n1->size > n2->size;
}


HuffmanTree::HuffmanTreeNode* HuffmanTree::HuffmanTreeNode::merge_two_nodes(
    HuffmanTree::HuffmanTreeNode *a, 
    HuffmanTree::HuffmanTreeNode *b
) {
    auto* result = new HuffmanTreeNode({
        {},
        a->size + b->size,
        a,
        b    
    });
    result->letters.insert(a->letters.begin(), a->letters.end());
    result->letters.insert(b->letters.begin(), b->letters.end());
    return result;
}

HuffmanTree::HuffmanTree(
    const std::map<unsigned char, size_t> &symbol_occurences
) {
    if (symbol_occurences.empty()) {
        root = new HuffmanTreeNode({
            {},
            0,
            nullptr,
            nullptr
        });
        return;
    }
    std::priority_queue <
        HuffmanTreeNode*, 
        std::vector<HuffmanTreeNode*>, 
        HuffmanTreeNodeCmp
    > vertexes;

    for (auto [symb, occur] : symbol_occurences) {
        vertexes.push(
            new HuffmanTreeNode({
                {symb},
                occur,
                nullptr,
                nullptr
            })
        );
    }    
    
    while (vertexes.size() > 2) {
        auto node1 = vertexes.top();
        vertexes.pop();
        auto node2 = vertexes.top();
        vertexes.pop();
        vertexes.push(
           HuffmanTreeNode::merge_two_nodes(node1, node2)
        );
    }
    if (vertexes.size() == 2) {
        auto node1 = vertexes.top();
        vertexes.pop();
        auto node2 = vertexes.top();
        vertexes.pop();
        root = HuffmanTreeNode::merge_two_nodes(node1, node2); 
    } else {
        auto node = vertexes.top();
        vertexes.pop();

        root = new HuffmanTreeNode({
            node->letters,
            node->size,
            node,
            nullptr
        });
    }
}
HuffmanTree::HuffmanTreeNode::~HuffmanTreeNode() {
    if (one_link != nullptr) {
        delete one_link;
    }
    if (zero_link != nullptr) {
        delete zero_link;
    }
}

HuffmanTree::~HuffmanTree() {
    delete root;
}

BitSequence HuffmanTree::get_code(unsigned char c) const {
    if (root->letters.count(c) == 0) {
        throw SymbolAbsentException(std::string("symbol absent"));
    }
    BitSequence answer;
    HuffmanTreeNode *current = root;
    while (current->zero_link != nullptr) {
        if (current->zero_link->letters.count(c)) {
            answer.add_bit(0);
            current = current->zero_link;
        } else {
            answer.add_bit(1);
            current = current->one_link;
        }
    }
    return answer;
}

size_t HuffmanTree::total_symbols() const {
    return root->size;
}

size_t HuffmanTree::size() const {
    return root->letters.size();
}

std::set<unsigned char> HuffmanTree::symbols() const {
    return root->letters;
}