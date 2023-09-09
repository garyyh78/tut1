CXX := g++
CXXFLAGS := -g -Wall -std=c++14

TARGET := runCompile
TESTDATA := testdata.lexer

lexer.o: Lexer.cpp Lexer.h
	$(CXX) $(CXXFLAGS) -c Lexer.cpp -o lexer.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(TARGET): *.o 
	$(CXX) $(CXXFLAGS) *.o -o $(TARGET)

clean:
	rm *.o 

test:
	$(TARGET) < $(TESTDATA)
