#include <iostream>
#include "Window.h"



int main() {
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();
	clock_t c_ticks, d_ticks;
	clock_t fps{ 0 };

	bool running = true;
	while (running) {
		//render
		if (!pWindow->ProcessMessages()) {
			std::cout << "Closing Window\n";
			running = false;
		}
		Sleep(10);
		pWindow->FPScounter();
	}

	delete pWindow;
	return 0;
}

