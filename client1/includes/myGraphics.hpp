// Client1

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <math.h>

class ActiveTexture {
	public:
		int biasX;
		int biasY;

		int x;
		int y;

		int hp;
		int side;
		bool Exists;

		int x1;
		int y1;

		sf::Image Obj_Image[4];
		sf::Texture Obj_Texture[4];
		sf::Sprite Obj_Sprite[4];

		ActiveTexture(std::string filepath[4]) {
			biasX = 123;
			biasY = -25;
			for (int i = 0; i < 4; i++) {
				if (!Obj_Image[i].loadFromFile(filepath[i])) {
					return;
				}
				if (!Obj_Texture[i].loadFromImage(Obj_Image[i])) {
					return;
				}
				Obj_Sprite[i].setTexture(Obj_Texture[i]);
				setPossition(0, 0);
			}
			hp = 3;
			side = 0;
			Exists = true;
			x1 = 0;
			y1 = 0;
		}

		~ActiveTexture() {
		}

		void move (int dx, int dy) {
			for (int i = 0; i < 4; i++) {
				Obj_Sprite[i].move(dx, dy);
			}
		}

		void setPossition(int posX, int posY) {
			x = posX - biasX;
			y = posY - biasY;
			for (int i = 0; i < 4; i++) {
				Obj_Sprite[i].setPosition(posX + biasX, posY + biasY);
			}
		}

		void draw(sf::RenderWindow &window, int posX, int posY, int id) {
			if ((id < 4) && (id >= 0)) {
				setPossition(posX, posY);
				x = posX - biasX;
				y = posY - biasY;
				window.draw(Obj_Sprite[id]);
				side = id;
			}
		}

		void draw(sf::RenderWindow &window, int posX, int posY) {
			if ((side < 4) && (side >= 0)) {
				setPossition(posX, posY);
				x = posX - biasX;
				y = posY - biasY;
				window.draw(Obj_Sprite[side]);
			}
		}

		void draw(sf::RenderWindow &window, int id) {
			if ((id < 4) && (id >= 0)) {
				window.draw(Obj_Sprite[id]);
				side = id;
			}
		}

		void draw(sf::RenderWindow &window) {
			if ((side < 4) && (side >= 0)) {
				window.draw(Obj_Sprite[side]);
			}
		}
};

class StaticTexture {
	public:
		sf::Image Obj_Image;
		sf::Texture Obj_Texture;
		sf::Sprite Obj_Sprite;

		StaticTexture(std::string filepath) {
			if (!Obj_Image.loadFromFile(filepath)) {
				return;
			}

			if (!Obj_Texture.loadFromImage(Obj_Image)) {
				return;
			}

			Obj_Sprite.setTexture(Obj_Texture);
			Obj_Sprite.setPosition(0, 0);
		}

		~StaticTexture() {
		}

		void setPossition(int x, int y) {
			Obj_Sprite.setPosition(x, y);
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
		return 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		return 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		return 4;
	}
	return -1;
}


















