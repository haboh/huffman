#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>

TEST_SUITE("test bitSequence") {
	TEST_CASE("empty") {
		BitSequence b;
		CHECK(b.size() == 0);
	}

	TEST_CASE("sample") {
		BitSequence b;
		b.add_bit(0);
		b.add_bit(1);
		b.add_bit(0);
		CHECK(b.size() == 3);
		CHECK(b.get_bit(0) == 0);
		CHECK(b.get_bit(1) == 1);
		CHECK(b.get_bit(2) == 0);	
	}


	TEST_CASE("all") {
		BitSequence b1;
		b1.add_bit(0);
		b1.add_bit(0);
		BitSequence b2;
		b2.add_bit(1);
		b2.add_bit(1);
		b2.add_bit(1);
		BitSequence b = b1 + b2;
		b1 += b2;
		CHECK(b == b1);
		CHECK(b.size() == 5);
		CHECK(b.get_bit(2) == 1);
	}

	TEST_CASE("plus") {
		BitSequence b1;
		b.add_bit(0);
		BitSequence b2;
		b2.add_bit(1);
		b2.add_bit(1);
		BitSequence b = b1 + b2;
		CHECK(b.size() == 3);
		CHECK(b.get_bit(0) == 0);
		CHECK(b.get_bit(1) == 1);
		CHECK(b.get_bit(2) == 0);
	}

	TEST_CASE("plusEqual") {
		BitSequence b1;
		b.add_bit(0);
		BitSequence b2;
		b2.add_bit(1);
		b2.add_bit(1);
		b1 += b2;
		CHECK(b1.size() == 3);
		CHECK(b1.get_bit(0) == 0);
		CHECK(b1.get_bit(1) == 1);
		CHECK(b1.get_bit(2) == 0);
	}
}