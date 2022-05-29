#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>
#include "writer.h"

TEST_SUITE("Test Writer") {
	TEST_CASE("test write int") {
		Writer* w = new Writer("testWriter.txt");
		w->write_int(3);
		delete w;
		std::ifstream in = std::ifstream("testWriter.txt");
		unsigned int r;
		in >> r;
		CHECK(r == 3);
		CHECK(!in);
	}

	TEST_CASE("test write byte") {
		Writer* w = new Writer("testWriter.txt");
		w->write_byte(3);
		delete w;
		std::ifstream in = std::ifstream("testWriter.txt");
		unsigned char r;
		in >> r;
		CHECK(r == 3);
		CHECK(!in);
	}

	TEST_CASE("test write bitsequence") {
		Writer* w = new Writer("testWriter.txt");
		BitSequence b;
		for (int i = 0; i < 7; i++) {
			b.add_bit(0);
		}
		b.add_bit(1);
		w->write_bits_sequence(b);
		delete w;
		std::ifstream in = std::ifstream("testWriter.txt");
		unsigned char r;
		in >> r;
		CHECK(r == 1);
		CHECK(!in);
	}

	TEST_CASE("test combinations") {
		Writer* w = new Writer("testWriter.txt");
		w->write_int(5);
		w->write_char(3);
		BitSequence b;
		for (int i = 0; i < 7; i++) {
			b.add_bit(0);
		}
		b.add_bit(1);
		w->write_bits_sequence(b);
		delete w;

		std::ifstream in = std::ifstream("testWriter.txt");
		unsigned int r1;
		in >> r1;
		CHECK(r1 == 5);
		CHECK(in);
		unsigned char r2;
		in >> r2;
		CHECK(r2 == 3);
		CHECK(in);
		in >> r2;
		CHECK(r2 == 1);
		CHECK(!in);
	}
}