#include <math.h>
#include <vector>

#define Tank_Velocity 5
#define Shell_Velocity 10
#define destruct 1  // Рушимый блок
#define non_destruct 2  // Нерушимый блок
#define blot 3  // Клякса

#define rows 26
#define cols 26

class Shell {
	public:
		int x;
		int y;
		int side;
		bool Exists;

		int cellX[2];
		int cellY[2];

		Shell() {
		}
		~Shell() {
		};
};

class Cup {
	public:
		int x;
		int y;
		int hp;

		Cup() {
			x = 25;
			y = 25 * 13;
			hp = 10;
		}
		~Cup() {
		}
};

class Tank {
	public:
		int x;
		int y;
		int hp;
		int id;
		int side;
		Shell shell;

		Tank() {
			shell.cellX[0] = -1;
			shell.cellX[1] = -1;
			shell.cellY[0] = -1;
			shell.cellY[1] = -1;
			shell.x = 0;
			shell.y = 0;
			x = 0;
			y = 0;
			side = 0;
			hp = 3;
			shell.Exists = false;
		}

		Tank(int posX, int posY) {
			shell.cellX[0] = -1;
			shell.cellX[1] = -1;
			shell.cellY[0] = -1;
			shell.cellY[1] = -1;
			shell.x = 0;
			shell.y = 0;
			x = posX;
			y = posY;	
			side = 0;
			hp = 2;
			shell.Exists = false;
		}

		~Tank() {
		};

		void setPossition(int posX, int posY) {
			x = posX;
			y = posY;
		}

		bool is_moving() {
			if ((id >= 0) && (id < 4)) {
				return true;
			}
			return false;
		}

		void align() {
			switch (side) {
				case 0:
					if (y % 25 < 2) {
						y = y - y % 25;
					} else {
						y = y - y % 25 + 25;
					}
					break;
				case 1:
					x = x - x % 25;
					break;
				case 2:
					y = y - y % 25;
					break;
				case 3:
					if (x % 25 < 2) {
						x = x - x % 25;
					} else {
						x = x - x % 25 + 25;
					}
					break;
			};
		}

		void move() {
			switch (id) {
				case 0:
					y -= Tank_Velocity;
					if (y < 25) {
						y = 25;
					}
					break;
				case 1:
					x += Tank_Velocity;
					if (x > 625) {
						x = 625;
					}
					break;
				case 2:
					y += Tank_Velocity;
					if (y > 625) {
						y = 625;
					}
					break;
				case 3:
					x -= Tank_Velocity;
					if (x < 25) {
						x = 25;
					}
			};
		}
};

void create_shell(Tank& tank) {
	if (tank.shell.Exists) {
		return;
	}
	tank.shell.Exists = true;
	tank.shell.side = tank.side;
	switch (tank.side) {
		case 0:
			tank.shell.x = tank.x;
			tank.shell.y = tank.y - 14;
			break;
		case 1:
			tank.shell.x = tank.x + 14;
			tank.shell.y = tank.y;
			break;
		case 2:
			tank.shell.x = tank.x;
			tank.shell.y = tank.y + 14;
			break;
		case 3:
			tank.shell.x = tank.x - 14;
			tank.shell.y = tank.y;
	};
	return;
}

bool hit_Cup(Shell& shell, Cup& cup) {
	if (!shell.Exists) {
		return false;
	}
	int dx = cup.x - shell.x;
	int dy = cup.y - shell.y;
	if ((abs(dx) <= 25) && (abs(dy) <= 25)) {
		cup.hp--;
		shell.Exists = false;
		return true;
	}
	return false;
}

bool hit_tank(Shell& shell, Tank& tank) {
	if (!shell.Exists) {
		return false;
	}
	int dx = tank.x - shell.x;
	int dy = tank.y - shell.y;
	if ((abs(dx) <= 25) && (abs(dy) <= 25)) {
		tank.hp--;
		shell.Exists = false;
		return true;
	}
	return false;
}

bool will_be_in_touch(Tank& tank, int** map) {
	int x = tank.x;
	int y = tank.y;
	switch (tank.id) {
		case 0:
			y -= Tank_Velocity;
			x = x / 26;
			y = y / 26;
			for (int i = 0; i < 2; i++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						return true;
					}
				}
				x++;
			}
			return false;
			break;
		case 1:
			x += Tank_Velocity;
			x = x / 26 + 1;
			y = y / 26;
			for (int i = 0; i < 2; i++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						return true;
					}
				}
				y++;
			}
			return false;
			break;
		case 2:
			y += Tank_Velocity;
			x = x / 26;
			y = y / 26 + 1;
			for (int i = 0; i < 2; i++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						return true;
					}
				}
				x++;
			}
			return false;
			break;
		case 3:
			x -= Tank_Velocity;
			x = x / 26;
			y = y / 26;
			for (int i = 0; i < 2; i++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						return true;
					}
				}
				y++;
			}
			return false;
	};
	return false;
}

bool is_in_touch(Shell& shell, int** map) {
	if (!shell.Exists) {
		return false;
	}
	int x = shell.x;
	int y = shell.y;	
	switch (shell.side) {
		case 0:
			x = x / 26;
			y = y / 26;
			for (int j = 0; j < 2; j++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						shell.Exists = false;
						if (map[x][y] == destruct) {
							map[x][y] = -1;
							shell.cellX[j] = x;
							shell.cellY[j] = y;
						}
					}
				}
				x++;
			}
			return true;
			break;
		case 1:
			x = x / 26 + 1;
			y = y / 26;
			for (int j = 0; j < 2; j++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						shell.Exists = false;
						if (map[x][y] == destruct) {
							map[x][y] = -1;
							shell.cellX[j] = x;
							shell.cellY[j] = y;
						}
					}
				}
				y++;
			}
			return true;
			break;
		case 2:
			x = x / 26;
			y = y / 26 + 1;
			for (int j = 0; j < 2; j++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						shell.Exists = false;
						if (map[x][y] == destruct) {
							map[x][y] = -1;
							shell.cellX[j] = x;
							shell.cellY[j] = y;
						}
					}
				}
				x++;
			}
			return true;
			break;
		case 3:
			x = x / 26;
			y = y / 26;
			for (int j = 0; j < 2; j++) {
				if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if ((map[x][y] == destruct) || (map[x][y] == non_destruct)) {
						shell.Exists = false;
						if (map[x][y] == destruct) {
							map[x][y] = -1;
							shell.cellX[j] = x;
							shell.cellY[j] = y;
						}
					}
				}
				y++;
			}
			return true;
	};
	return false;
}

bool will_touch(Tank& tank, Cup& cup) {
	int dx = tank.x - cup.x;
	int dy = tank.y - cup.y;
	switch (tank.id) {
		case 0:
			dy -= Tank_Velocity;
			if ((abs(dx) <= 25) && (dy > 0) && (dy < 50)) {
				return true;
			}
			return false;
			break;
		case 1:
			dx += Tank_Velocity;
			if ((abs(dy) <= 25) && (dx < 0) && (dx > -50)) {
				return true;
			}
			return false;
			break;
		case 2:
			dy += Tank_Velocity;
			if ((abs(dx) <= 25) && (dy < 0) && (dy > -50)) {
				return true;
			}
			return false;
			break;
		case 3:
			dx -= Tank_Velocity;
			if ((abs(dy) <= 25) && (dx > 0) && (dx < 50)) {
				return true;
			}
			return false;
	};
	return false;
}

bool will_touch(Tank& tank1, Tank& tank2) {
	int dx = tank1.x - tank2.x;
	int dy = tank1.y - tank2.y;
	switch (tank1.id) {
		case 0:
			dy -= Tank_Velocity;
			if ((abs(dx) <= 25) && (dy > 0) && (dy < 50)) {
				return true;
			}
			return false;
			break;
		case 1:
			dx += Tank_Velocity;
			if ((abs(dy) <= 25) && (dx < 0) && (dx > -50)) {
				return true;
			}
			return false;
			break;
		case 2:
			dy += Tank_Velocity;
			if ((abs(dx) <= 25) && (dy < 0) && (dy > -50)) {
				return true;
			}
			return false;
			break;
		case 3:
			dx -= Tank_Velocity;
			if ((abs(dy) <= 25) && (dx > 0) && (dx < 50)) {
				return true;
			}
			return false;
	};
	return false;
}

void move_tanks(std::vector<Tank>& Tanks, Cup& cup, int** map) {
	for (int i = 0; i < Tanks.size(); i++) {
		if (Tanks[i].id == 4) {
			create_shell(Tanks[i]);
		} else {
			bool touch = false;
			for (int j = 0; j < i; j++) {
				if (will_touch(Tanks[i], Tanks[j])) {
					touch = true;
				}
			}
			for (int j = i + 1; j < Tanks.size(); j++) {
				if (will_touch(Tanks[i], Tanks[j])) {
					touch = true;
				}
			}
			if (will_touch(Tanks[i], cup)) {
				touch = true;
			}
			if (!touch) {
				if (will_be_in_touch(Tanks[i], map)) {
					Tanks[i].align();
				} else {
					Tanks[i].move();
				}
			}
		}
	}
}

void move_shells(std::vector<Tank>& Tanks, int** map) {
	for (int i = 0; i < Tanks.size(); i++) {
		if (Tanks[i].shell.Exists) {
			switch(Tanks[i].shell.side) {
				case 0:
					Tanks[i].shell.y -= Shell_Velocity;
					if (Tanks[i].shell.y < 0) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 1:
					Tanks[i].shell.x += Shell_Velocity;
					if (Tanks[i].shell.x > 650) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 2:
					Tanks[i].shell.y += Shell_Velocity;
					if (Tanks[i].shell.y > 650) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 3:
					Tanks[i].shell.x -= Shell_Velocity;
					if (Tanks[i].shell.x < 0) {
						Tanks[i].shell.Exists = false;
					}
			};
		}
	}
}

int move_all(std::vector<Tank>& Tanks, Cup& cup, int** map) {
	for (int i = 0; i < Tanks.size(); i++) {
		if ((Tanks[i].id < 4) && (Tanks[i].id >= 0)) {
			if (Tanks[i].side != Tanks[i].id) {
				Tanks[i].align();
				Tanks[i].side = Tanks[i].id;
			}
		} else {
			Tanks[i].align();
		}
	}
	move_tanks(Tanks, cup, map);
	move_shells(Tanks, map);
	for (int i = 0; i < Tanks.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (hit_tank(Tanks[j].shell, Tanks[i])) {
			}
		}
		for (int j = i + 1; j < Tanks.size(); j++) {
			if (hit_tank(Tanks[j].shell, Tanks[i])) {
			}
		}
		if (hit_Cup(Tanks[i].shell, cup)) {
			if (cup.hp <= 0) {
				return i;
			}
		}
	}
	for (int i = 0; i < Tanks.size(); i++) {
		if (is_in_touch(Tanks[i].shell, map)) {
		}
	}
	int count_of_alive = 0;
	int id = 0;
	for (int i = 0; i < Tanks.size(); i++) {
		if (Tanks[i].hp > 0) {
			count_of_alive++;
			id = i;
		}
	}
	if (count_of_alive <= 1) {
		return id;
	}
	return -1;
}





















