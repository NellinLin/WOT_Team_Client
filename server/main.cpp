// SERVER
#include <SFML/Network.hpp>
#include <iostream>
#include "includes/tank.hpp"

int main() {
	Tank Tank1(0, 0);
	Tank Tank2(200, 0);

	sf::Time fps = sf::milliseconds(31);

	sf::TcpListener listener;
	if (listener.listen(8022) != sf::Socket::Done) {
		return -2;
	}

	sf::TcpSocket client1;
	sf::TcpSocket client2;
	while ((listener.accept(client1) != sf::Socket::Done)) {
	}
	std::cout << "Client1 connected" << std::endl;

	while ((listener.accept(client2) != sf::Socket::Done)) {
	}
	std::cout << "Client2 connected" << std::endl;

	int id = 0;
	sf::Packet packet;

	while (true) {
		client1.receive(packet);
		packet >> id;
		if (id == 100) {
			client1.disconnect();
			client2.disconnect();
			return 0;
		}
		Tank1.move(id);
		packet.clear();

		client2.receive(packet);
		packet >> id;
		if (id == 100) {
			client1.disconnect();
			client2.disconnect();
			return 0;
		}
		Tank2.move(id);
		packet.clear();

		packet << Tank1.x << Tank1.y << Tank1.side << Tank2.x << Tank2.y << Tank2.side;
		client1.send(packet);
		client2.send(packet);
		packet.clear();
		sleep(fps);
	}
	return 0;
}
