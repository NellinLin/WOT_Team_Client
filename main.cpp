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

	myTexture Tank1_Up("pvp_draw/t011.png");
	myTexture Tank1_Right("pvp_draw/t021.png");
	myTexture Tank1_Down("pvp_draw/t031.png");
	myTexture Tank1_Left("pvp_draw/t041.png");

	myTexture Tank2_Up("pvp_draw/t012.png");
	myTexture Tank2_Right("pvp_draw/t022.png");
	myTexture Tank2_Down("pvp_draw/t032.png");
	myTexture Tank2_Left("pvp_draw/t042.png");

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
	sf::sleep(sf::seconds(5));

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

	Tank2_Up.setPossition(200, 200);
	sf::Music music;
	if (!music.openFromFile("audio/mexican.ogg")) {
		std::cout << "can't open audio" << std::endl;
	}
	music.play();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		Game_Board.draw(window);
		Tank2_Up.draw(window);
		Tank2_Right.draw(window, 200, 100);
		Tank2_Down.draw(window, 300, 100);
		Tank2_Left.draw(window, 400, 100);

		if (key_id() == 1) {
			Tank2_Up.move(window, 0, -1);
		}
		if (key_id() == 2) {
			Tank2_Up.move(window, 1, 0);
		}
		if (key_id() == 3) {
			Tank2_Up.move(window, 0, 1);
		}
		if (key_id() == 4) {
			Tank2_Up.move(window, -1, 0);
		}

		window.display();
	}

	return 0;
}

	
