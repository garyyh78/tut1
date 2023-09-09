#ifndef PARSER_H
#define PARSER_H

#include"AST.h"
#include"Lexer.h"

class Parser {
public:
	Parser(): lexer( new Lexer() ) {}
	~Parser() { delete lexer_; }

	ASTUniPtr parseNumberExpr();

private:
	void getNextToken();

	ASTUniPtr logError(const std::string& str) const;
	ProtoASTUniPtr LogErrorProto(const std::string& str) const;

	int cur_tok_;
	Lexer *lexer_;
	static std::map<char, int> binaryOpsPrecendence;
};

#endif
