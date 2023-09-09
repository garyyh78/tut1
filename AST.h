#ifndef AST_H
#define AST_H

#include<string>

class ExprASTBase {
public: 
	virtual ~ExprASTBase() = default;
};

using ASTUniPtr = std::unique_ptr<ExprASTBase>;

class NumberExprAST : public ExprASTBase {
public:
	NumberExprAST(double val): val_(val) {}

private: 
	double val_;
};

class VarExprAST : public ExprASTBase {
public:
	VarExprAST(const std::string name): name_(name) {}

private: 
	std::string name_;
};

class BinaryExprAST : public ExprASTBase {
public:
	BinaryExprAST(char op,
				  ASTUniPtr lhs,
			   	  ASTUniPtr rhs)
	: op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

private: 
	char op_;
  	ASTUniPtr lhs_, rhs_;
};

class FuncCallExprAST : public ExprASTBase {
public:
	FuncCallExprAST(const std::string &callee,
				  std::vector<ASTUniPtr> args)
	: callee_(callee), args_(std::move(args)) {}

private:
  	std::string callee_;
  	std::vector<ASTUniPtr> args_;
};

class PrototypeAST {
public:
	PrototypeAST(const std::string &name,
				 std::vector<std::string> args)
	: name_(name), args_(std::move(args)) {}

  const std::string &getName() const { return name_; }

private:
  std::string name_;
  std::vector<std::string> args_;

};

using ProtoASTUniPtr = std::unique_ptr<PrototypeAST>;

class FunctionAST {
public:
	FunctionAST(std::unique_ptr<PrototypeAST> proto,
		        ASTUniPtr body)
	: proto_(std::move(proto)), body_(std::move(body)) {}

private:
  std::unique_ptr<PrototypeAST> proto_;
  ASTUniPtr body_;

};
#endif
