CXX := g++
CXXFLAGS := -g -Wall -std=c++14

TARGET := runCompile
TESTDATA := testdata.lexer

mainloop.o: MainLoop.cpp MainLoop.h
	$(CXX) $(CXXFLAGS) -c MainLoop -o $@

lexer.o: Lexer.cpp Lexer.h
	$(CXX) $(CXXFLAGS) -c Lexer.cpp -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

$(TARGET): *.o 
	$(CXX) $(CXXFLAGS) *.o -o $(TARGET)

clean:
	rm *.o 

test:
	$(TARGET) < $(TESTDATA)
