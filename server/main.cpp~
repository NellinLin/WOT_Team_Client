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
			for (int j = 0; j < 2; j++) {
				if ((Tanks[i].shell.cellX[j] > 0) && (Tanks[i].shell.cellX[j] < cols) && (Tanks[i].shell.cellY[j] > 0) && (Tanks[i].shell.cellY[j] < rows)) {
					packet << Tanks[i].shell.cellX[j] << Tanks[i].shell.cellY[j];
					Tanks[i].shell.cellX[j] = -1;
					Tanks[i].shell.cellY[j] = -1;
				}
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
