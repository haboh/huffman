#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>

TEST_SUITE("test HuffmanTree") {
	TEST_CASE("one symbol test") {
		std::map<unsigned char,size_t> occur = {
			{'a', 1}
		};
		HuffmanTree tree(occur);
		BitSequence result = tree.get_code('a');
		CHECK(result.get_size() == 1);
		CHECK(result.get_bit(0) == 0);
    }
	TEST_CASE("sample test") {
		std::map<unsigned char, size_t> occur = {
			{'a', 2},
			{'b', 3},
			{'z', 1}
		};
		HuffmanTree tree(occur);
        BitSequence result_a = tree.get_code('a');
		BitSequence result_b = tree.get_code('b');
		BitSequence result_z = tree.get_code('z');

        CHECK(result_b.get_bit(0) == 0);
        CHECK(result_a.get_bit(0) == 1);
        CHECK(result_z.get_bit(0) == 1);
        CHECK(result_a.get_bit(1) == 1);
        CHECK(result_z.get_bit(1) == 0); 
        CHECK(result_a.get_size() == 2);
		CHECK(result_b.get_size() == 1);
		CHECK(result_z.get_size() == 2);
	}
    

    TEST_CASE("empty test") {
        std::map<unsigned char, size_t> occur = {};
        HuffmanTree tree(occur);

        CHECK(tree.size() == 0);
    }
}
