#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "includes/myGraphics.hpp"

int main() {
	// Обязательно должно быть в коде до *_*
	myTexture Game_Board("pvp_draw/Game_Board.png");
	myTexture Heart("pvp_draw/Heart.png");
	myTexture Klaksa("pvp_draw/Klaksa.png");
	myTexture Ner_Blok("pvp_draw/Ner_blok.png");
	myTexture Nerush_Blok("pvp_draw/Nerush_blok.png");
	myTexture Strelka("pvp_draw/Strelka.png");

	std::string tank1[4] = {"pvp_draw/t011.png", "pvp_draw/t021.png", "pvp_draw/t031.png", "pvp_draw/t041.png"};
	Tank Tank1(tank1);

	std::string tank2[4] = {"pvp_draw/t011.png", "pvp_draw/t022.png", "pvp_draw/t032.png", "pvp_draw/t042.png"};
	Tank Tank2(tank2);

	myTexture exit("interface/exit.png");
	myTexture Interf_1("interface/Interf_1.png");
	myTexture Interf_2("interface/Interf_2.png");
	myTexture Interf_3("interface/Interf_3.png");
	myTexture Play("interface/Play.png");
	myTexture Setting("interface/Settings.png");
	myTexture top("interface/top.png");

	sf::RenderWindow window(sf::VideoMode(952, 650), "tan4iki");
	// *_*

	// Пример кода.

	window.clear();
	Interf_1.draw(window);
	window.display();
	sf::sleep(sf::seconds(1.5));
	int id = 0;
	while (window.isOpen() && !id) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		Interf_2.draw(window, 0, 0);
		Play.draw(window, 70, 250);
		Setting.draw(window, 70, 350);
		top.draw(window, 70, 450);
		exit.draw(window, 840, 20);

		if (exit.isPressed(window)) {
			window.close();
		}

		if (Play.isPressed(window)) {   // Проверка на нажатие кнопки "Play"
			id = 1;
		}

		window.display();
	}

	if (id != 1) {  // Если не нажали кнопку "Play", выходим из программы
		return 0;
	}

	sf::Music music;
	if (!music.openFromFile("audio/7NatArmy.ogg")) {
		std::cout << "can't open audio" << std::endl;
	}
	music.play();

	int x = 197;
	int y = 200;
	Tank2.setPossition(x, y);
	int side = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		while ((id = key_id()) == 0) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			y += -1;
			window.clear();
			Game_Board.draw(window);
			Tank2.draw(window, x, y, id);
			window.display();
			sf::sleep(sf::seconds(1.0 / 30));
			side = 0;
		}

		while ((id = key_id()) == 1) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			x += 1;
			window.clear();
			Game_Board.draw(window);
			Tank2.draw(window, x, y, id);
			window.display();
			sf::sleep(sf::seconds(1.0 / 30));
			side = 1;
		}
		while ((id = key_id()) == 2) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			y += 1;
			window.clear();
			Game_Board.draw(window);
			Tank2.draw(window, x, y, id);
			window.display();
			sf::sleep(sf::seconds(1.0 / 50));
			side = 2;
		}
		while ((id = key_id()) == 3) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			x += -1;
			window.clear();
			Game_Board.draw(window);
			Tank2.draw(window, x, y, id);
			window.display();
			sf::sleep(sf::seconds(1.0 / 50));
			side = 3;
		}
		window.clear();
		Game_Board.draw(window);
		Tank2.draw(window, side);
		window.display();
		sf::sleep(sf::seconds(0.001));
	}

	return 0;
}

	
