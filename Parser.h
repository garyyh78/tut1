#ifndef PARSER_H
#define PARSER_H

#include <map>

#include "AST.h"
#include "Lexer.h"

class Parser {
public:
	Parser(): lexer_(new Lexer()) {}
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

	void fetchNextToken();
	int getCurrentToken() const { return cur_tok_; }

	std::string getCurrentId() const { return lexer_->getCurrentId(); }
	double getCurrentNumVal() const { return lexer_->getCurrentNumVal(); }

private:
	int getTokenPrecedence() const;

	ASTUniPtr logError(const std::string& str) const;
	ProtoASTUniPtr logErrorProto(const std::string& str) const;

	int cur_tok_;
	Lexer *lexer_;

	static std::map<char, int> binaryOpsPrec;
};

#endif
