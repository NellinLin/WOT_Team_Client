// SERVER
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "includes/tank.hpp"

const int n = 2;

int main() {
	int n = 2;
	std::vector<Tank> Tanks(n);

	Tanks[0].setPossition(25, 25);
	Tanks[1].setPossition(200, 200);

	sf::TcpSocket clients[n];

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
	map[16][15] = 1;
	map[15][15] = 1;

	sf::Time fps = sf::milliseconds(31);

	sf::TcpListener listener;
	if (listener.listen(9003) != sf::Socket::Done) {
		return -2;
	}

	for (int i = 0; i < n; i++) {
		while ((listener.accept(clients[i]) != sf::Socket::Done)) {
		}
		std::cout << i << " Client connected" << std::endl;
	}

	sf::Packet packet;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}

	int game_stopped = 0;

	while (true) {
		for (int i = 0; i < n; i++) {
			packet.clear();
			clients[i].receive(packet);
			packet >> Tanks[i].id;
			if (Tanks[i].id == 100) {
				for (int j = 0; j < n; j++) {
					clients[j].disconnect();
				}
				return 0;
			}
		}

		move_all(Tanks, map);

		int count_of_alive = 0;
		for (int i = 0; i < Tanks.size(); i++) {
			if (Tanks[i]. hp > 0) {
				count_of_alive++;
			}
		}
		packet.clear();
		if (count_of_alive <= 1) {
			game_stopped = 1;
			packet << game_stopped;
			for (int j = 0; j < 5; j++) {
				for (int i = 0; i < n; i++) {
					clients[i].send(packet);
				}
				sf::sleep(fps);
			}
			std::cout << game_stopped << std::endl;
			return 0;
		}
		game_stopped = 0;
		packet << game_stopped;

		for (int i = 0; i < Tanks.size(); i++) {
			packet << Tanks[i].x << Tanks[i].y << Tanks[i].side << Tanks[i].hp;
		}
		for (int i = 0; i < Tanks.size(); i++) {
			packet << Tanks[i].shell.x << Tanks[i].shell.y << Tanks[i].shell.side << Tanks[i].shell.Exists;
		}

		for (int i = 0; i < Tanks.size(); i++) {
			if ((Tanks[i].shell.cellX1 > 0) && (Tanks[i].shell.cellX1 < cols) && (Tanks[i].shell.cellY1 > 0) && (Tanks[i].shell.cellY1 < rows)) {
				packet << Tanks[i].shell.cellX1 << Tanks[i].shell.cellY1;
				Tanks[i].shell.cellX1 = -1;
				Tanks[i].shell.cellY1 = -1;
			}
			if ((Tanks[i].shell.cellX2 > 0) && (Tanks[i].shell.cellX2 < cols) && (Tanks[i].shell.cellY2 > 0) && (Tanks[i].shell.cellY2 < rows)) {
				packet << Tanks[i].shell.cellX2 << Tanks[i].shell.cellY2;
				Tanks[i].shell.cellX2 = -1;
				Tanks[i].shell.cellY2 = -1;
			}
		}

		for (int i = 0; i < n; i++) {
			clients[i].send(packet);
		}
		packet.clear();
		sleep(fps);
	}
	return 0;
}
