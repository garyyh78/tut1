#include<string>
#include<map>

static std::map<char, int> Parser::binaryOpsPrecedence = 
	{{'+', 1}, {'-', 2}, {'*', 4}, {'/', 8}};

void Parser::fetchNextToken() {
	cur_tok_ = lexer_->getToken();
}

ASTUniPtr logError(const std::string& str) const {
	std::count << "PARSE ERROR: " << str << std::rndl;
	return nullptr;
}

ProtoASTUniPtr LogErrorProto(const std::string& str) const {
	logError(str);
	 return nullptr;
}

ASTUniPtr Parser::parseNumberExpr() {
	auto res_ptr = std::make_unique<NumberExprAST>(lexer_->getNumVal());
	fetchNextToken(); 
	return std::move(res_ptr);
}

ASTUniPtr parseBracketExpr() {
  getNextToken(); 

  auto res_ptr = ParseExpression();
  if(!res_ptr)
    return nullptr;

  if (cur_tok_ != ')')
    return LogError("expected ')'");

  getNextToken(); 

  return res_ptr;
}

static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;

  getNextToken();  // eat identifier.

  if (CurTok != '(') // Simple variable ref.
    return std::make_unique<VariableExprAST>(IdName);

  // Call.
  getNextToken();  // eat (
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurTok != ')') {
    while (true) {
      if (auto Arg = ParseExpression())
        Args.push_back(std::move(Arg));
      else
        return nullptr;

      if (CurTok == ')')
        break;

      if (CurTok != ',')
        return LogError("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();

  return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

static std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}

static std::unique_ptr<ExprAST> ParsePrimary() {
  switch (CurTok) {
  default:
    return LogError("unknown token when expecting an expression");
  case tok_identifier:
    return ParseIdentifierExpr();
  case tok_number:
    return ParseNumberExpr();
  case '(':
    return ParseParenExpr();
  }
}
