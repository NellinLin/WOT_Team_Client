// SERVER
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "includes/tank.hpp"
#include "includes/map.hpp"

const int n = 2;

int main() {
	Cup cup;
	int n = 2;
	std::vector<Tank> Tanks(n);

	Tanks[0].setPossition(100, 25);
	Tanks[1].setPossition(100, 625);

	sf::TcpSocket clients[n];

	int** map;
	map = Read_from_file("maps/map1.txt");
	if (map == NULL) {
		return -1;
	}

	sf::Time fps = sf::milliseconds(31);

	sf::TcpListener listener;
	if (listener.listen(9007) != sf::Socket::Done) {
		return -2;
	}

	for (int i = 0; i < n; i++) {
		while ((listener.accept(clients[i]) != sf::Socket::Done)) {
		}
		std::cout << i << " Client connected" << std::endl;
	}

	sf::Packet packet;

	while (true) {
		for (int i = 0; i < n; i++) {
			packet.clear();
			clients[i].receive(packet);
			packet >> Tanks[i].id;
			if (Tanks[i].id == 100) {
				for (int j = 0; j < n; j++) {
					packet.clear();
					packet << 2;
					clients[j].send(packet);
					clients[j].disconnect();
				}
				return 0;
			}
		}

		int champion = move_all(Tanks, cup, map);
		if (champion >= 0) {
			if (champion < Tanks.size()) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < champion; j++) {
						packet.clear();
						packet << 0;
						clients[j].send(packet);
					}
					packet.clear();
					packet << 1;
					clients[champion].send(packet);
					for (int j = champion; j < Tanks.size(); j++) {
						packet.clear();
						packet << 0;
						clients[j].send(packet);
					}
					sleep(fps);
				}
			} else {
				for (int i = 0; i < Tanks.size(); i++) {
					packet.clear();
					packet << 5;
					clients[i].send(packet);
				}
			}
			for (int i = 0 ; i < Tanks.size(); i++) {
				clients[i].disconnect();
			}
			return 0;
		}
		packet.clear();
		packet << -1;

		for (int i = 0; i < Tanks.size(); i++) {
			packet << Tanks[i].x << Tanks[i].y << Tanks[i].side << Tanks[i].hp;
		}
		for (int i = 0; i < Tanks.size(); i++) {
			packet << Tanks[i].shell.x << Tanks[i].shell.y << Tanks[i].shell.side << Tanks[i].shell.Exists;
		}

		for (int i = 0; i < Tanks.size(); i++) {
			for (int j = 0; j < 2; j++) {
				if ((Tanks[i].shell.cellX[j] >= 0) && (Tanks[i].shell.cellX[j] < cols) && (Tanks[i].shell.cellY[j] >= 0) && (Tanks[i].shell.cellY[j] < rows)) {
					packet << Tanks[i].shell.cellX[j] << Tanks[i].shell.cellY[j];
					Tanks[i].shell.cellX[j] = -1;
					Tanks[i].shell.cellY[j] = -1;
				}
			}
		}
		packet << cup.x << cup.y << cup.hp;
		for (int i = 0; i < n; i++) {
			clients[i].send(packet);
		}
		packet.clear();
		sleep(fps);
	}
	return 0;
}
