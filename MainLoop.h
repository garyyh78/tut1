#ifndef MAINLOOP_H
#define MAINLOOP_H

#include"Lexer.h"

class MainLoop {

public : 
	MainLoop(): lexer_(new Lexer()){ } 
	~MainLoop() { delete lexer_; } 

	MainLoop(const MainLoop&) = delete;
	MainLoop(MainLoop&&) = delete;
	MainLoop& operator= (const MainLoop&) = delete;
	MainLoop& operator= (MainLoop&&) = delete;

	void runMainLoop() const;

private:
	Lexer *lexer_;
};

#endif
