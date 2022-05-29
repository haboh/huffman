CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = hw-02_huffman
SRCDIR = src
OBJDIR = obj
TESTDIR = test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE)

testHuffmanTree: test/test_huffman_tree.cpp $(OBJDIR)/huffmanTree.o $(OBJDIR)/BitSequence.o
	$(CXX) test/test_huffman_tree.cpp $(CXXFLAGS) -c -MMD -o  $(OBJDIR)/test_huffman_tree.o
	$(CXX) $(OBJDIR)/test_huffman_tree.o $(OBJDIR)/huffmanTree.o $(OBJDIR)/BitSequence.o  $(LDFLAGS) -o testHuffmanTree
	./testHuffmanTree

.PHONY: clean all

