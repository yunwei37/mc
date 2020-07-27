#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "app.h"

int main() {
	if (app::createApp() != -1) {
		app::run();
	}
}