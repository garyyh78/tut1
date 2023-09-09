#include<iostream> 
#include"Lexer.h"
#include"Token.h"

bool Lexer::isLastCharPartOfNumber() const {
	return(isdigit(lastchar_) || lastchar_ == '.');
};

bool Lexer::isNotEndOfLine() const {
	return(lastchar_ != EOF && lastchar_ != '\n' && lastchar_ != '\r');
};

int Lexer::getToken() {

	// skip space
	while(isspace(lastchar_))
	  	lastchar_ = getchar();

	// first is alphabet : def, intern, variable names
	if(isalpha(lastchar_)){
		identifier_ = lastchar_;
		while(isalnum(lastchar_=getchar()))
			identifier_ += lastchar_;
		
		if(identifier_ == "def")
			return tok_def;

		if(identifier_ == "extern")
			return tok_extern;

		return tok_identifier;	
	}

	// numbers
	if(isLastCharPartOfNumber()) {
	    std::string s;
	    do {
			s += lastchar_;
			lastchar_ = getchar();
	    } while(isLastCharPartOfNumber());

		numval_ = strtod(s.c_str(), nullptr);
	    return tok_number;
  	}

	// comments
  	if(lastchar_ == '#') {
    	do {
      		lastchar_ = getchar();
		} while(isNotEndOfLine());
	
   		if(lastchar_ != EOF)
			return getToken();
	}

	// until finish
  	if(lastchar_ == EOF)
    	return tok_eof;

	// Otherwise, just return the character as its ascii value.
  	int c = lastchar_;
	lastchar_ = getchar();
  	return c;
}
