#ifndef LEXER_H
#define LEXER_H

#include<string>
#include"Token.h" 

class Lexer {

public:
	Lexer() : lastchar_(' ') {}

	Lexer(const Lexer&) = delete;
	Lexer(Lexer&&) = delete;
	Lexer& operator= (const Lexer&) = delete;
	Lexer& operator= (Lexer&&) = delete;

	int getToken();
	std::string getIdentifier() const { return identifier_; } 
	double getNumVal() const { return numval_; } 

private:

	bool isLastCharPartOfNumber() const;
	bool isNotEndOfLine() const;

	int lastchar_;
	std::string identifier_;
	double numval_;
};

#endif
