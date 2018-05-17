#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "myGraphics.hpp"
#include "map.hpp"

const int CONTINUE_THE_GAME = 10;
const int WIN = 20;
const int LOSE = 30;

#define rows 26
#define cols 26

int start(sf::RenderWindow& window, bool first_open) {
	StaticTexture Game_Board("pvp_draw/Game_Board.png");
	StaticTexture Heart("pvp_draw/Heart.png");
	StaticTexture Klaksa("pvp_draw/Klaksa.png");
	StaticTexture Ner_Blok("pvp_draw/Ner_blok.png");
	StaticTexture Nerush_Blok("pvp_draw/Nerush_blok.png");
	StaticTexture Strelka("pvp_draw/Strelka.png");
	StaticTexture Cup("pvp_draw/Cup.png");

	StaticTexture exit("interface/exit.png");
	StaticTexture Interf_1("interface/Interf_1.png");
	StaticTexture Interf_2("interface/Interf_2.png");
	StaticTexture Interf_3("interface/Interf_3.png");
	StaticTexture Interf_4("interface/Interf_4.png");
	StaticTexture Interf_5("interface/Interf_5.png");
	StaticTexture Interf_6("interface/Interf_6.png");
	StaticTexture Off_music("interface/Off.png");
	StaticTexture On_music("interface/On.png");
	StaticTexture Play("interface/Play.png");

	std::string tank1[4] = {"pvp_draw/t11_up.png", "pvp_draw/t11_right.png", "pvp_draw/t11_down.png", "pvp_draw/t11_left.png"};
	ActiveTexture Tank1(tank1);
	std::string tank2[4] = {"pvp_draw/t21_up.png", "pvp_draw/t21_right.png", "pvp_draw/t21_down.png", "pvp_draw/t21_left.png"};
	ActiveTexture Tank2(tank2);
	std::string tank3[4] = {"pvp_draw/t31_up.png", "pvp_draw/t31_right.png", "pvp_draw/t31_down.png", "pvp_draw/t31_left.png"};
	ActiveTexture Tank3(tank3);

	std::string shell[4] = {"pvp_draw/Pula1.png", "pvp_draw/Pula2.png", "pvp_draw/Pula3.png", "pvp_draw/Pula4.png"};
	ActiveTexture Shell1(shell);
	ActiveTexture Shell2(shell);
	ActiveTexture Shell3(shell);

	std::vector<ActiveTexture> Tanks;
	Tanks.push_back(Tank1);
	Tanks.push_back(Tank2);
	Tanks.push_back(Tank3);

	std::vector<ActiveTexture> Shells;
	Shells.push_back(Shell1);
	Shells.push_back(Shell2);
	Shells.push_back(Shell3);
	for (int i = 0; i < Shells.size(); i++) {
		Shells[i].biasX += 25;
	}

	int** map;
	map = Read_from_file("maps/map1.txt");
	if (map == NULL) {
		return -1;
	}

	if (first_open) {
		window.clear();
		Interf_1.draw(window);
		window.display();
		sf::sleep(sf::seconds(1.0));
	}
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
		Play.draw(window, 70, 350);
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
		return -1;
	}

	sf::Music music;
	if (!music.openFromFile("audio/7NatArmy.ogg")) {
		std::cout << "can't open audio" << std::endl;
	}
	// music.play();

	sf::TcpSocket server;
	sf::Socket::Status status = server.connect("192.168.0.102", 9022);

	if (status != sf::Socket::Done) {
		window.close();
		return 1;
	}

	int The_End = 0;
	bool GAME_IS_ON = true;

	while (window.isOpen() && GAME_IS_ON) {
		sf::Event event;
		sf::Packet packet;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed || exit.isPressed(window)) {
			id = 100;
			packet.clear();
			packet << id;
			server.send(packet);
			server.disconnect();
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				GAME_IS_ON = false;
			}
		}
		int id = key_id();

		packet.clear();
		packet << id;
		server.send(packet);
		packet.clear();
		server.receive(packet);

		packet >> The_End;
		if (The_End != CONTINUE_THE_GAME) {
			GAME_IS_ON = false;
			server.disconnect();
		}

		int tanks_count = 0;
		int shell_count = 0;
		packet >> tanks_count >> shell_count;
		for (int i = 0; i < tanks_count; i++) {
			packet >> Tanks[i].x1 >> Tanks[i].y1 >> Tanks[i].side >> Tanks[i].hp;
		}
		for (int i = 0; i < shell_count; i++) {
			packet >> Shells[i].x1 >> Shells[i].y1 >> Shells[i].side;
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

		for (int i = 0; i < tanks_count; i++) {
			Tanks[i].setPossition(Tanks[i].x1, Tanks[i].y1);
		}
		for (int i = 0; i < shell_count; i++) {
			Shells[i].setPossition(Shells[i].x1, Shells[i].y1);
		}

		window.clear();
		Game_Board.draw(window);
		for (int i = 0; i < tanks_count; i++) {
			if (i < Tanks.size()) {
				Tanks[i].draw(window);
			}
		}
		for (int i = 0; i < shell_count; i++) {
			if (i < Shells.size()) {
				if (Shells[i].side == 1) {
					Shells[i].draw(window, Shells[i].x1 - 10, Shells[i].y1 + 20);
				} else if (Shells[i].side == 3) {
					Shells[i].draw(window, Shells[i].x1, Shells[i].y1 + 20);
				} else if (Shells[i].side == 0) {
					Shells[i].draw(window, Shells[i].x1 - 5, Shells[i].y1 + 25);
				} else if (Shells[i].side == 2) {
					Shells[i].draw(window, Shells[i].x1 - 5, Shells[i].y1 + 15);
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
		Cup.draw(window, 148, 25 * 12);
		exit.draw(window, 840, 20);
		window.display();
		sf::sleep(sf::milliseconds(15));
	}
	if (window.isOpen()) {
		window.clear();
		if (The_End == WIN) {
			Interf_5.draw(window);
		} else {
			Interf_6.draw(window);
		}
		window.display();
		sf::sleep(sf::seconds(2.0));
		return 1;
	}
	return -1;
}
