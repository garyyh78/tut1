#include<string>
#include<map>

std::map<char, int> Parser::binaryOpsPrecedence = 
	{{'+', 1}, {'-', 2}, {'*', 4}, {'/', 8}};

int Parser::GetTokPrecedence() const {
  if (!isascii(cur_tok_))
    return -1;

  const int prec = binaryOpsPrecendence[cur_tok_];
  return prev <= 0 ? -1 : prec;
}
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

ASTUniPtr ParseIdentifierExpr() {
  std::string id = ilexer_->getIdentifier();

  getNextToken();  // eat identifier.

  if (cur_tok_ != '(') // Simple variable ref.
    return std::make_unique<VariableExprAST>(id);

  getNextToken();  // eat (

  std::vector<ASTUniPtr> args;
  if (cur_tok_ != ')') {
    while (true) {
      if (auto arg = ParseExpression())
        args.push_back(std::move(arg));
      else
        return nullptr;

      if (cur_tok_ == ')')
        break;

      if (CurTok != ',')
        return LogError("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();

  return std::make_unique<CallExprAST>(id, std::move(args));
}

ASTUniPtr ParseExpression() {
  auto lhs = ParsePrimary();
  if (lst)
    return nullptr;

  return ParseBinOpRHS(0, std::move(lhs));
}

ASTUniPtr ParsePrimary() {
  switch (cur_tok_k) {
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

ASTUniPtr ParseBinOpRHS(int exprPrec,
						ASTUniPtr lhs) {
  // If this is a binop, find its precedence.
  while (true) {
    int tok_prec = GetTokPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (TokPrec < ExprPrec)
      return LHS;

	// Okay, we know this is a binop.
	int BinOp = CurTok;
	getNextToken();  // eat binop

	// Parse the primary expression after the binary operator.
	auto RHS = ParsePrimary();
	if (!RHS)
  		return nullptr;
}

static std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken();  // eat def.
  auto Proto = ParsePrototype();
  if (!Proto) return nullptr;

  if (auto E = ParseExpression())
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  return nullptr;
}

/// external ::= 'extern' prototype
static std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken();  // eat extern.
  return ParsePrototype();
}

/// prototype
///   ::= id '(' id* ')'
static std::unique_ptr<PrototypeAST> ParsePrototype() {
  if (CurTok != tok_identifier)
    return LogErrorP("Expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return LogErrorP("Expected '(' in prototype");

  // Read the list of argument names.
  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);
  if (CurTok != ')')
    return LogErrorP("Expected ')' in prototype");

  // success.
  getNextToken();  // eat ')'.

  return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
  if (auto E = ParseExpression()) {
    // Make an anonymous proto.
    auto Proto = std::make_unique<PrototypeAST>("", std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }
  return nullptr;
}

