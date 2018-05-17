// SERVER
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "project/include/tank.hpp"
#include "project/include/map.hpp"

const int CONTINUE_THE_GAME = 10;
const int WIN = 20;
const int LOSE = 30;

int main() {
	int n = 0;
	std::cout << "Enter number of players: ";
	std::cin >> n;
	Cup cup;
	if ((n < 2) || (n > 3)) {
		std::cerr << "COUNT_OF_PLAYERS_IS_FEW_OR_MANY" << std::endl;
		return 0;
	}
	std::vector<Tank> Tanks(n);
	for (int i = 0; i < Tanks.size() / 2; i++) {
		Tanks[2 * i].setPossition(100 + i * 100, 20);
		Tanks[2 * i + 1].setPossition(100 + i * 100, 625);
	}
	if (Tanks.size() % 2 != 0) {
		Tanks[Tanks.size() - 1].setPossition(625, 325);
	}
	sf::TcpSocket clients[n];
	int num_of_client[n];
	int** map;
	map = Read_from_file("maps/map1.txt");
	if (map == NULL) {
		return -1;
	}

	sf::Time fps = sf::milliseconds(31);

	sf::TcpListener listener;
	if (listener.listen(9022) != sf::Socket::Done) {
		return -2;
	}

	for (int i = 0; i < n; i++) {
		while ((listener.accept(clients[i]) != sf::Socket::Done)) {
		}
		std::cout << i << " Client connected" << std::endl;
		num_of_client[i] = i;
	}

	sf::Packet packet;
	while (true) {
		for (int i = 0; i < Tanks.size(); i++) {
			packet.clear();
			clients[num_of_client[i]].receive(packet);
			packet >> Tanks[i].id;
			if (Tanks[i].id == 100) {
				clients[num_of_client[i]].disconnect();
				for (int j = i; j < Tanks.size() - 1; i++) {
					num_of_client[i] = num_of_client[i + 1];
				}
				Tanks.erase(Tanks.begin() + i);
			}
		}

		if (Tanks.size() == 1) {
			packet.clear();
			packet << WIN;
			clients[num_of_client[0]].send(packet);
			clients[num_of_client[0]].disconnect();
			listener.close();
			return 0;
		}
		if (Tanks.size() == 0) {
			listener.close();
			return 0;
		}

		int champion = move_all(Tanks, cup, map);
		for (int i = 0; i < Tanks.size(); i++) {
			if (Tanks[i].hp <= 0) {
				packet.clear();
				packet << LOSE;
				clients[num_of_client[i]].send(packet);
				for (int j = i; j < Tanks.size() - 1; j++) {
					num_of_client[j] = num_of_client[j + 1];
				}
				Tanks.erase(Tanks.begin() + i);
			}
		}
		int tanks_count = Tanks.size();
		int shell_count = 0;
		for (int i = 0; i < Tanks.size(); i++) {
			if (Tanks[i].shell.Exists) {
				shell_count++;
			}
		}

		if (tanks_count  <= 1) {
			if (tanks_count == 1) {
				packet.clear();
				packet << WIN;
				clients[num_of_client[0]].send(packet);
				clients[num_of_client[0]].disconnect();
				listener.close();
				return 0;
			} else {
				listener.close();
				return 0;
			}
		}

		if (champion >= 0) {
			if (champion < Tanks.size()) {
				for (int j = 0; j < champion; j++) {
					packet.clear();
					packet << LOSE;
					clients[num_of_client[j]].send(packet);
				}
				packet.clear();
				packet << WIN;
				clients[champion].send(packet);
				for (int j = champion; j < Tanks.size(); j++) {
					packet.clear();
					packet << LOSE;
					clients[num_of_client[j]].send(packet);
				}
				sleep(fps);
			} else {
				for (int i = 0; i < Tanks.size(); i++) {
					packet.clear();
					packet << WIN;
					clients[num_of_client[i]].send(packet);
				}
			}
			for (int i = 0 ; i < Tanks.size(); i++) {
				clients[num_of_client[i]].disconnect();
			}
			listener.close();
			return 0;
		}

		packet.clear();
		packet << CONTINUE_THE_GAME << tanks_count << shell_count;

		for (int i = 0; i < Tanks.size(); i++) {
			packet << Tanks[i].x << Tanks[i].y << Tanks[i].side << Tanks[i].hp;
		}
		for (int i = 0; i < Tanks.size(); i++) {
			if (Tanks[i].shell.Exists) {
				packet << Tanks[i].shell.x << Tanks[i].shell.y << Tanks[i].shell.side;
			}
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
		for (int i = 0; i < n; i++) {
			clients[num_of_client[i]].send(packet);
		}
		packet.clear();
		sleep(fps);
	}
	for (int i = 0 ; i < Tanks.size(); i++) {
		clients[num_of_client[i]].disconnect();
	}
	listener.close();
	return 0;
}
