#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "Parser.h"

class MainLoop {

public : 
	MainLoop(): parser_(new Parser()){ } 
	~MainLoop() { delete parser_; } 

	MainLoop(const MainLoop&) = delete;
	MainLoop(MainLoop&&) = delete;
	MainLoop& operator= (const MainLoop&) = delete;
	MainLoop& operator= (MainLoop&&) = delete;

	void runMainLoop();

private:

	void fetchNextToken();
	void processDefinition();
	void processExtern();
	void processTopLevelExpression();
	void processIgnoreNoOp();

	Parser *parser_;
};

#endif
