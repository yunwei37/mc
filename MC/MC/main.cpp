#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "app/app.h"

int main() {
	App app;
	return app.run();
}