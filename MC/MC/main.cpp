#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "app.h"

int main() {
	App app;
	return app.run();
}