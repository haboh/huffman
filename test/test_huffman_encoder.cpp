#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>
#include "huffman.h"

TEST_SUITE("HuffmanEncoder") {
	TEST_CASE("Sample") {
		zip("testData/sample.txt", "tmp-output.txt");
		unzip("tmp-output.txt", "sampe-output.txt");
		std::system("diff testData/sample.txt sampe-output.txt");
	}

	TEST_CASE("Bigg") {
		zip("testData/big.txt", "tmp-output.txt");
		unzip("tmp-output.txt", "sampe-output.txt");
		std::system("diff testData/big.txt sampe-output.txt");
	}
}