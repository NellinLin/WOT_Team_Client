// CLIENT1
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "includes/myGraphics.hpp"

#define biasX 148
#define T1 0  // Indexes of ActiveTexture
#define T2 1
#define S1 2
#define S2 3

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

	std::vector<ActiveTexture> Textures;
	Textures.push_back(Tank1);
	Textures.push_back(Tank2);
	Textures.push_back(Shell1);
	Textures.push_back(Shell2);


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

	sf::TcpSocket server;
	sf::Socket::Status status = server.connect("127.0.1.1", 8022);

	if (status != sf::Socket::Done) {
		window.close();
		return -1;
	}

	Textures[T1].Exists = true;
	Textures[T2].Exists = true;
	Textures[S1].Exists = false;
	Textures[S2].Exists = false;

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
		if ((id >= 0) && (id < 4)) {
			Tank1.side = id;
		}
		packet.clear();
		packet << id;
		server.send(packet);
		server.receive(packet);
		packet >> Textures[T1].x1 >> Textures[T1].y1 >> Textures[T1].side >> Textures[T2].x1 >> Textures[T2].y1 >> Textures[T2].side;
		packet.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < Textures.size(); j++) {
				if (Textures[j].Exists) {
					int dx = (Textures[j].x1 - Textures[j].x + biasX) / 3;
					int dy = (Textures[j].y1 - Textures[j].y) / 3;
					Textures[j].move(dx, dy);
				}
			}
			sf::sleep(sf::milliseconds(7));
		}
		for (int i = 0; i < Textures.size(); i++) {
			Textures[i].setPossition(Textures[i].x1, Textures[i].y1);
		}
		packet.clear();
		window.clear();
		Game_Board.draw(window);
		for (int i = 0; i < Textures.size(); i++) {
			if (Textures[i].Exists) {
				Textures[i].draw(window);
			}
		}
		window.display();
		sf::sleep(sf::milliseconds(7));
	}

	return 0;
}
