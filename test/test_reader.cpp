#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <map>
#include <huffmanTree.h>
#include <bitsequence.h>
#include "reader.h"

TEST_SUITE("Test reader") {
	TEST_CASE("test read int") {
		Reader r = Reader("testData/int.txt");
		unsigned int res = r.read_int();
		CHECK(res == 1234);
	}

	TEST_CASE("test read byte") {
		Reader r = Reader("testData/one.txt");
		unsigned char res = r.read_byte();
		CHECK(res == 'f');
	}

	TEST_CASE("test read bitsequence") {
		Reader r = Reader("testData/one.txt");
		BitSequence res = r.read_bitSequence();
		BitSequence should;
		should.add_bit(0);
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(1);
		CHECK(res == should);
	}

	TEST_CASE("test combinations") {
		Reader r = Reader("testData/sample.txt");
		unsigned int res1 = r.read_int();
		unsigned char res2 = r.read_byte();	
		BitSequence res3 = r.read_bitSequence();
		BitSequence should;
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(0);
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(0);
		should.add_bit(1);
		should.add_bit(0);
		CHECK(res1 == 6345);
		CHECK(res2 == 52);
		CHECK(res3 == should);
	}
}