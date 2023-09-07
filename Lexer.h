#ifndef LEXER_H
#define LEXER_H

#include<string>
#include"Token.h" 

class Lexer {

public:
	Lexer() : lastchar_(' ') {};
	Lexer(const Lexer&) = delete;
	Lexer& operator= (const Lexer&) = delete;

	void run();
private:

	int getToken();
	bool isLastCharPartOfNumber() const;
	bool isNotEndOfLine() const;

	int lastchar_;
	std::string identifier_;
	double numval_;
};

#endif
