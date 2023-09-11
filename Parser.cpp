#include <iostream>
#include <string>
#include <map>

#include "Parser.h"

std::map<char, int> Parser::binaryOpsPrec = 
	{{'+', 1}, {'-', 2}, {'*', 4}, {'/', 8}};

int Parser::getTokenPrecedence() const {
  if (!isascii(cur_tok_))
    return -1;

  const int prec = binaryOpsPrec[cur_tok_];
  return prec <= 0 ? -1 : prec;
}

void Parser::fetchNextToken() {
	cur_tok_ = lexer_->getToken();
}

ASTUniPtr logError(const std::string& str) {
	std::cout << "PARSE ERROR: " << str << std::endl;
	return nullptr;
}

ProtoASTUniPtr logErrorProto(const std::string& str) {
	logError(str);
	return nullptr;
}

ASTUniPtr Parser::parseNumberExpr() {
	auto res_ptr = std::make_unique<NumberExprAST>(lexer_->getCurrentNumVal());
	fetchNextToken(); 
	return std::move(res_ptr);
}

ASTUniPtr Parser::parseBracketExpr() {
  fetchNextToken(); 

  auto res_ptr = parseExpression();
  if(!res_ptr)
    return nullptr;

  if (cur_tok_ != ')')
    return logError("expected ')'");

  fetchNextToken(); 

  return res_ptr;
}

ASTUniPtr Parser::parseIdentifierExpr() {
  std::string id = lexer_->getCurrentId();

  fetchNextToken();  // eat identifier.

  if (cur_tok_ != '(') // Simple variable ref.
    return std::make_unique<VarExprAST>(id);

  fetchNextToken();  // eat (

  std::vector<ASTUniPtr> args;
  if (cur_tok_ != ')') {
    while (true) {
      if (auto arg = parseExpression())
        args.push_back(std::move(arg));
      else
        return nullptr;

      if (cur_tok_ == ')')
        break;

      if (cur_tok_ != ',')
        return logError("Expected ')' or ',' in argument list");
      fetchNextToken();
    }
  }

  // Eat the ')'.
  fetchNextToken();

  return std::make_unique<FuncCallExprAST>(id, std::move(args));
}

ASTUniPtr Parser::parseExpression() {
  auto lhs = parsePrimary();
  if (lhs)
    return nullptr;

  return parseBinOpsRHS(0, std::move(lhs));
}

ASTUniPtr Parser::parsePrimary() {
  switch (cur_tok_) {
  default:
    return logError("unknown token when expecting an expression");
  case tok_identifier:
    return parseIdentifierExpr();
  case tok_number:
    return parseNumberExpr();
  case '(':
    return parseBracketExpr();
  }
}

ASTUniPtr Parser::parseBinOpsRHS(int exprPrec, ASTUniPtr lhs) {
  // If this is a binop, find its precedence.
  while (true) {
    int tok_prec = getTokenPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (tok_prec < exprPrec)
      return lhs;

	// Okay, we know this is a binop.
	int BinOp = cur_tok_;
	fetchNextToken();  // eat binop

	// Parse the primary expression after the binary operator.
	auto rhs = parsePrimary();
	if (!rhs)
  		return nullptr;
	}	
}

std::unique_ptr<FunctionAST> Parser::parseDefinition() {
  fetchNextToken();  // eat def.

  auto proto = parsePrototype();
  if (!proto)
	return nullptr;

  if (auto e = parseExpression())
    return std::make_unique<FunctionAST>(std::move(proto), std::move(e));

  return nullptr;
}

/// external ::= 'extern' prototype
std::unique_ptr<PrototypeAST> Parser::parseExtern() {
  fetchNextToken();  // eat extern.
  return parsePrototype();
}

/// prototype
///   ::= id '(' id* ')'
std::unique_ptr<PrototypeAST> Parser::parsePrototype() {
  if (CurTok != tok_identifier)
    return logErrorP("Expected function name in prototype");

  std::string fnName = lexer_->getCurrentId();
  fetchNextToken();

  if (CurTok != '(')
    return logErrorP("Expected '(' in prototype");

  // Read the list of argument names.
  std::vector<std::string> argNames;
  while (getNextToken() == tok_identifier)
    argNames.push_back(lexer_->getCurrentIdentifier());
  if (CurTok != ')')
    return logErrorP("Expected ')' in prototype");

  // success.
  fetchNextToken();  // eat ')'.

  return std::make_unique<PrototypeAST>(fnName, std::move(argNames));
}

std::unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
  if (auto e = parseExpression()) {
    // Make an anonymous proto.
    auto proto = std::make_unique<PrototypeAST>("", std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(proto), std::move(e));
  }
  return nullptr;
}
