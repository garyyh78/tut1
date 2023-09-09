#include <iostream>
#include "MainLoop.h"

int main() {
	MainLoop *mainloop = new MainLoop();
	mainloop->runMainLoop();
	delete mainloop;
}
