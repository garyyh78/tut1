#include <iostream> 
#include "MainLoop.h"
#include "Token.h"

void MainLoop::processDefinition() {
	if(!parser_->parseDefinition())
		fetchNextToken();
}

void MainLoop::processExtern() {
	if(!parser_->parseExtern())
    	fetchNextToken();
}

void MainLoop::processTopLevelExpression() {
	if(!parser_->parseTopLevelExpr())
    	fetchNextToken();
}

void MainLoop::processIgnoreNoOp() {
	fetchNextToken();
}

void MainLoop::fetchNextToken() {
	parser_->fetchNextToken();
}

void MainLoop::runMainLoop() {
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
				std::cout << "/NUM:" << "(" << parser_->getCurrentNumVal() << ")/ ";
				processTopLevelExpression();
	      		break;
		    case tok_identifier:
				std::cout << "/ID:" << "(" << parser_->getCurrentId() << ")/ ";
				processTopLevelExpression();
	      		break;
			default:
				std::cout << "/TOK:" << "(" << char(cur_tok) << ")/ ";
				processTopLevelExpression();
	      		break;
    	}
  	}
};
