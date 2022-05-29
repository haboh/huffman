#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>
#include "huffman.h"

TEST_SUITE("TestCounter") {
	TEST_CASE("empty") {
		auto result = count_symbols_occurence("testData/empty.txt");
		CHECK(result == std::map<unsigned char, size_t>());
	}

	TEST_CASE("sample") {
		auto result = count_symbols_occurence("testData/sample.txt");
		std::map<unsigned char, size_t> answer = {
			{'П', 2},
			{'п', 10},
			{'р', 10},
			{'и', 10},
			{'в', 10},
			{'е', 10},
			{'т', 10},
			{' ', 10},
			{'!', 2}
		};
		CHECK(result == answer);
	}

	TEST_CASE("one symbol") {
		auto result = count_symbols_occurence("testData/one.txt");
		std:map<unsigned char, size_t> answer = {
			{"f", 1}
		};
		CHECK(result == answer);
	}
}