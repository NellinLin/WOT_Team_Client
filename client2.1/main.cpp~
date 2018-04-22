// CLIENT2
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

#include "includes/myGraphics.hpp"

#define biasX 148

int main() {
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
		Setting.draw(window, 70, 370);
		top.draw(window, 70, 490);
		exit.draw(window, 840, 20);

		if (exit.isPressed(window)) {
			window.close();
		}

		if (Play.isPressed(window)) {
			id = 1;
		}

		window.display();
	}

	if (!window.isOpen() && (id != 1)) {
		return 0;
	}

	sf::Music music;
	if (!music.openFromFile("audio/7NatArmy.ogg")) {
		std::cout << "can't open audio" << std::endl;
	}
	// music.play();
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int side = 0;

	sf::TcpSocket server;
	sf::Socket::Status status = server.connect("127.0.1.1", 8014);

	if (status != sf::Socket::Done) {
		window.close();
		return -1;
	}

	while (window.isOpen()) {
		sf::Event event;
		sf::Packet packet;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			id = 100;
			packet << id;
			server.send(packet);
			server.disconnect();
			window.close();
			return 0;
		}
		int id = key_id();
		if (id >= 0) {
			side = id;
		}
		packet.clear();
		packet << id;
		server.send(packet);
		server.receive(packet);
		packet >> x1 >> y1 >> x2 >> y2;

		int dx1 = Tank1.x - x1;
		int dy1 = Tank1.y - y1;
		if ((abs(dx1) < 5) && !dx1) {
			for (int i = 0; i < abs(dx1); i++) {
				Tank1.move(1, 0);
				sleep(sf::milliseconds(9));
				window.clear();
				Game_Board.draw(window);
				Tank1.draw(window, x1 + biasX, y1, side);
			}
		} else if ((abs(dy1) < 5) && !dy1) {
			for (int i = 0; i < abs(dy1); i++) {
				Tank1.move(0, 1);
				sleep(sf::milliseconds(9));
				window.clear();
				Game_Board.draw(window);
				Tank1.draw(window, x1 + biasX, y1, side);
			}
		} else {
			Tank1.setPossition(x1, y1);
		}

		int dx2 = Tank2.x - x2;
		int dy2 = Tank2.y - y2;
		if ((abs(dx2) < 5) && !dx2) {
			for (int i = 0; i < abs(dx2); i++) {
				Tank2.move(1, 0);
				sleep(sf::milliseconds(9));
				window.clear();
				Game_Board.draw(window);
				Tank2.draw(window, x2 + biasX, y2, side);
			}
		} else if ((abs(dy2) < 5) && !dy2) {
			for (int i = 0; i < abs(dy2); i++) {
				Tank2.move(0, 1);
				sleep(sf::milliseconds(9));
				window.clear();
				Game_Board.draw(window);
				Tank2.draw(window, x2 + biasX, y2, side);
			}
		} else {
			Tank2.setPossition(x2, y2);
		}
		packet.clear();
		window.clear();
		Game_Board.draw(window);
		Tank1.draw(window, x1 + biasX, y1, side);
		Tank2.draw(window, x2 + biasX, y2, side);
		window.display();
	}

	return 0;
}
