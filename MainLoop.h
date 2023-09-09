#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "Parser.h"

class MainLoop {

public : 
	MainLoop(): parser_(new Parserr()){ } 
	~MainLoop() { delete parser_; } 

	MainLoop(const MainLoop&) = delete;
	MainLoop(MainLoop&&) = delete;
	MainLoop& operator= (const MainLoop&) = delete;
	MainLoop& operator= (MainLoop&&) = delete;

	void runMainLoop() const;

private:

	void fetchNextToken() const;

	void processDefinition() const;
	void processExtern() const;
	void processTopLevelExpression() const;
	void processIgnoreNoOp() const;

	const Parser *parser_;
};

#endif
