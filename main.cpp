#include <iostream>
#include "Lexer.h"

int main() {
	Lexer *lexer = new Lexer();
	lexer->run();
	delete lexer;
}
