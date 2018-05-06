// CLIENT1
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "includes/myGraphics.hpp"

#define rows 26
#define cols 26

int main() {
	StaticTexture Game_Board("pvp_draw/Game_Board.png");
	StaticTexture Heart("pvp_draw/Heart.png");
	StaticTexture Klaksa("pvp_draw/Klaksa.png");
	StaticTexture Ner_Blok("pvp_draw/Ner_blok.png");
	StaticTexture Nerush_Blok("pvp_draw/Nerush_blok.png");
	StaticTexture Strelka("pvp_draw/Strelka.png");

	StaticTexture exit("interface/exit.png");
	StaticTexture Interf_1("interface/Interf_1.png");
	StaticTexture Interf_2("interface/Interf_2.png");
	StaticTexture Interf_3("interface/Interf_3.png");
	StaticTexture Interf_4("interface/Interf_4.png");
	StaticTexture Off_music("interface/Off.png");
	StaticTexture On_music("interface/On.png");
	StaticTexture Play("interface/Play.png");
	StaticTexture Setting("interface/Settings.png");
	StaticTexture top("interface/top.png");

	std::string tank1[4] = {"pvp_draw/t011.png", "pvp_draw/t021.png", "pvp_draw/t031.png", "pvp_draw/t041.png"};
	ActiveTexture Tank1(tank1);

	std::string tank2[4] = {"pvp_draw/t011.png", "pvp_draw/t022.png", "pvp_draw/t032.png", "pvp_draw/t042.png"};
	ActiveTexture Tank2(tank2);

	std::string shell[4] = {"pvp_draw/Pula1.png", "pvp_draw/Pula2.png", "pvp_draw/Pula3.png", "pvp_draw/Pula4.png"};
	ActiveTexture Shell1(shell);
	ActiveTexture Shell2(shell);

	std::vector<ActiveTexture> Tanks;
	Tanks.push_back(Tank1);
	Tanks.push_back(Tank2);

	std::vector<ActiveTexture> Shells;
	Shells.push_back(Shell1);
	Shells.push_back(Shell2);
	for (int i = 0; i < Shells.size(); i++) {
		Shells[i].biasX += 25;
	}

	int** map;
	map = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		map[i] = (int*)malloc(cols * sizeof(int));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 5; i < cols - 5; i++) {
		map[15][i] = 1;
	}
	for (int i = 5; i < cols - 5; i++) {
		map[16][i] = 1;
	}
	for (int i = 5; i < cols - 5; i++) {
		map[17][i] = 1;
	}
	for (int i = 5; i < cols - 5; i++) {
		map[20][i] = 2;
	}
	for (int i = 5; i < cols - 5; i++) {
		map[10][i] = 3;
	}

	sf::RenderWindow window(sf::VideoMode(952, 650), "tan4iki");

	window.clear();
	Interf_1.draw(window);
	window.display();
	sf::sleep(sf::seconds(1.0));
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

	sf::TcpSocket server;
	sf::Socket::Status status = server.connect("127.0.0.1", 9003);

	if (status != sf::Socket::Done) {
		window.close();
		return -1;
	}

	Tanks[0].Exists = true;
	Tanks[1].Exists = true;
	Shells[0].Exists = false;
	Shells[1].Exists = false;
	int game_stopped = 0;

	while (window.isOpen()) {
		sf::Event event;
		sf::Packet packet;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			id = 100;
			packet.clear();
			packet << id;
			server.send(packet);
			server.disconnect();
			window.close();
			return 0;
		}
		int id = key_id();
		if ((id >= 0) && (id < 4)) {
			Tank1.side = id;
		}

		packet.clear();
		packet << id;
		server.send(packet);
		packet.clear();
		server.receive(packet);

		packet >> game_stopped;
		if (game_stopped == 1) {
			window.close();
			server.disconnect();
			return 0;
		}
		for (int i = 0; i < Tanks.size(); i++) {
			packet >> Tanks[i].x1 >> Tanks[i].y1 >> Tanks[i].side >> Tanks[i].hp;
		}
		for (int i = 0; i < Shells.size(); i++) {
			packet >> Shells[i].x1 >> Shells[i].y1 >> Shells[i].side >> Shells[i].Exists;
		}
		for (int i = 0; i < 2 * Tanks.size(); i++) {
			int x = 0;
			int y = 0;
			packet >> x >> y;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
				map[x][y] = -1;
			}
		}
		packet.clear();

		for (int i = 0; i < Tanks.size(); i++) {
			Tanks[i].setPossition(Tanks[i].x1, Tanks[i].y1);
		}
		for (int i = 0; i < Tanks.size(); i++) {
			Shells[i].setPossition(Shells[i].x1, Shells[i].y1);
		}
		window.clear();
		Game_Board.draw(window);
		for (int i = 0; i < Tanks.size(); i++) {
			Tanks[i].draw(window);
		}
		for (int i = 0; i < Shells.size(); i++) {
			if (Shells[i].Exists) {
				if ((Shells[i].side == 1) || (Shells[i].side == 3)) {
					Shells[i].draw(window, Shells[i].x1, Shells[i].y1 + 20);
				} else if ((Shells[i].side == 0) || (Shells[i].side == 2)) {
					Shells[i].draw(window, Shells[i].x1 - 5, Shells[i].y1 + 10);
				}
			}
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				switch (map[i][j]) {
					case 1:
						Ner_Blok.draw(window, i * 25 + 148, j * 25);
						break;
					case 2:
						Nerush_Blok.draw(window, i * 25 + 148, j * 25);
						break;
					case 3:
						Klaksa.draw(window, i * 25 + 148, j * 25);
						break;
				};
			}
		}

		window.display();
		sf::sleep(sf::milliseconds(15));
	}

	return 0;
}
