
#include "app.h"

int main() {
	if (app::createApp() != -1) {
		app::run();
	}
}