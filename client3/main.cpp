#include "project/include/GameProcess.hpp"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(952, 650), "tan4iki");
	bool first_open = true;
	while (true) {
		int result = start(window, first_open);
		first_open = false;
		if (result < 0) {
			return 0;
		}
	}
	return 0;
}
