#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

class myTexture {
	public:
		sf::Image Obj_Image;
		sf::Texture Obj_Texture;
		sf::Sprite Obj_Sprite;

		myTexture(std::string filepath) {
			if (!Obj_Image.loadFromFile(filepath)) {
				return;
			}

			if (!Obj_Texture.loadFromImage(Obj_Image)) {
				return;
			}

			Obj_Sprite.setTexture(Obj_Texture);
			Obj_Sprite.setPosition(0, 0);
		}

		~myTexture() {
		}

		void setPossition(int x, int y) {
			Obj_Sprite.setPosition(x, y);
		}

		void move(sf::RenderWindow &window, int x, int y) {
			Obj_Sprite.move(x, y);
			window.draw(Obj_Sprite);
		}

		void draw(sf::RenderWindow &window, int x, int y) {
			Obj_Sprite.setPosition(x, y);
			window.draw(Obj_Sprite);
		}

		void draw(sf::RenderWindow &window) {
			window.draw(Obj_Sprite);
		}

		int isPressed(sf::RenderWindow &window) {
			sf::Event event;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
				if (Obj_Sprite.getGlobalBounds().contains(pos.x, pos.y)) {
					return 1;
				}
				return 0;
			}
			return 0;
		}
};

int key_id() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		return 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		return 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return 4;
	}
	return -1;
}
