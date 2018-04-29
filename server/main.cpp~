// SERVER
#include <SFML/Network.hpp>
#include <iostream>
#include "includes/tank.hpp"

int main() {
	Tank Tank1(0, 0);
	Tank Tank2(200, 600);
	Shell Shell1;
	Shell Shell2;

	sf::Time fps = sf::milliseconds(31);

	sf::TcpListener listener;
	if (listener.listen(9000) != sf::Socket::Done) {
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

	int id1 = 0;
	int id2 = 0;
	sf::Packet packet;

	while (true) {
		client1.receive(packet);
		packet >> id1;
		if (id1 == 100) {
			client1.disconnect();
			client2.disconnect();
			return 0;
		}
		packet.clear();

		client2.receive(packet);
		packet >> id2;
		if (id2 == 100) {
			client1.disconnect();
			client2.disconnect();
			return 0;
		}
		move_Tanks(Tank1, id1, Tank2, id2, Shell1, Shell2);
		move_Shell(Shell1, Tank2);
		move_Shell(Shell2, Tank1);
		packet.clear();

		packet << Tank1.x << Tank1.y << Tank1.side << Tank1.hp 
			<< Tank2.x << Tank2.y << Tank2.side << Tank2.hp
			<< Shell1.Exists << Shell1.x << Shell1.y << Shell1.side
			<< Shell2.Exists << Shell2.x << Shell2.y << Shell2.side;

		client1.send(packet);
		client2.send(packet);
		packet.clear();
		sleep(fps);
	}
	return 0;
}
