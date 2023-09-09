#ifndef PARSER_H
#define PARSER_H

#include"AST.h"
#include"Lexer.h"

class Parser {
public:
	Parser(): lexer( new Lexer() ) {}
	~Parser() { delete lexer_; }

	ASTUniPtr parseNumberExpr();
	ASTUniPtr parseBracketExpr();
	ASTUniPtr parseExpression();
	ASTUniPtr parsePrototype();
	ASTUniPtr parseDefinition();
	ASTUniPtr parseTopLevelExpr();
	ASTUniPtr parseExtern();
	ASTUniPtr parseIdentifierExpr();
	ASTUniPtr parsePrimary();
	ASTUniPtr parseBinOpsRHS(int, ASTUniPtr);

	void getNextToken();

private:
	int getTokenPrecedence() const;

	ASTUniPtr logError(const std::string& str) const;
	ProtoASTUniPtr LogErrorProto(const std::string& str) const;

	int cur_tok_;
	Lexer *lexer_;
	static std::map<char, int> binaryOpsPrecendence;
};

#endif
