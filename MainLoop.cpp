#include <iostream> 
#include "MainLoop.h"
#include "Token.h"

void MainLoop::processDefinition() const {
	if(!parser_->parseDefinition())
		fetchNextToken();
}

void MainLoop::processExtern() const {
	if(!parser_->parseExtern())
    	fetchNextToken();
}

void MainLoop::processTopLevelExpression() const {
	if(!parser_->parseTopLevelExpr())
    	fetchNextToken();
}

void MainLoop::processIgnoreNoOp() const {
	fetchNextToken();
}

void MainLoop::fectNextToken() const {
	parser_->fetchNextToken();
}

void MainLoop::runMainLoop() const {
	while(true) {
		const int cur_tok = parser_->getCurrentToken();
		switch(cur_tok) {
			case tok_eof:
				std::cout << "/EOF/\n";
		   		return;
		    case ';': 
				std::cout << "/NO-OP/ ";
		    	processIgnoreNoOp();
		      	break;
		    case tok_def:
				std::cout << "/DEF/ ";
				processDefinition();
		    	break;
		    case tok_extern:
				std::cout << "/EXTERN/ ";
				processExtern();
		      	break;
		    case tok_number:
				std::cout << "/NUM:" << "(" << lexer_->getNumVal() << ")/ ";
				processTopLevelExpression();
	      		break;
		    case tok_identifier:
				std::cout << "/ID:" << "(" << lexer_->getIdentifier() << ")/ ";
				processTopLevelExpression();
	      		break;
			default:
				std::cout << "/TOK:" << "(" << char(cur_tok) << ")/ ";
				processTopLevelExpression();
	      		break;
    	}
  	}
};
