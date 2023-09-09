#include<iostream> 
#include"MainLoop.h"
#include"Token.h"

void MainLoop::runMainLoop() const {
	int cur_tok_ = lexer_->getToken();
	while(true) {
		switch(cur_tok_) {
			case tok_eof:
				std::cout << "/EOF/\n";
		   		return;
		    case ';': // ignore top-level semicolons.
		    	cur_tok_ = lexer_->getToken();
		      	break;
		    case tok_def:
				std::cout << "/DEF/ ";
				cur_tok_ = lexer_->getToken();
		    	break;
		    case tok_extern:
				std::cout << "/EXTERN/ ";
				cur_tok_ = lexer_->getToken();
		      	break;
		    case tok_number:
				std::cout << "/NUM:" << "(" << lexer_->getNumVal() << ")/ ";
				cur_tok_ = lexer_->getToken();
	      		break;
		    case tok_identifier:
				std::cout << "/ID:" << "(" << lexer_->getIdentifier() << ")/ ";
				cur_tok_ = lexer_->getToken();
	      		break;
			default:
				std::cout << "/TOK:" << "(" << char(cur_tok_) << ")/ ";
				cur_tok_ = lexer_->getToken();
	      		break;
    	}
  	}
};
