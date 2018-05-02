#include <math.h>
#include <vector>

#define Tank_Velocity 5
#define Shell_Velocity 10
#define destruct 1  // Рушимый блок
#define non_destuct 2  // Нерушимый блок
#define blot 3  // Клякса

#define rows 26
#define cols 26

/*


	Поставить координаты танка в центр, а не в левый верхний угл :     DONE


*/

class Shell {
	public:
		int x;
		int y;
		int side;
		bool Exists;

		int cellX1;
		int cellY1;
		int cellX2;
		int cellY2;

		Shell() {
		}

		~Shell() {
		};
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
			shell.cellX1 = -1;
			shell.cellY1 = -1;
			shell.cellX2 = -1;
			shell.cellY2 = -1;
			shell.x = 0;
			shell.y = 0;
			x = 0;
			y = 0;
			side = 0;
			hp = 2;
			shell.Exists = false;
		}

		Tank(int posX, int posY) {
			shell.cellX1 = -1;
			shell.cellY1 = -1;
			shell.cellX2 = -1;
			shell.cellY2 = -1;
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
			if ((x % 25) < 15) {
				x = x - x % 25;
			} else {
				x = x - x % 25 + 25;
			}
			if ((y % 25) < 15) {
				y = y - y % 25;
			} else {
				y = y - y % 25 + 25;
			}
		}

		void move() {
			if (id != side) {
				align();
				if ((id < 4) && (id >= 0)) {
					side = id;
				}
			}
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
			tank.shell.y = tank.y - 26;				
			break;
		case 1:
			tank.shell.x = tank.x + 26;
			tank.shell.y = tank.y;
			break;
		case 2:
			tank.shell.x = tank.x;
			tank.shell.y = tank.y + 26;
			break;
		case 3:
			tank.shell.x = tank.x - 26;
			tank.shell.y = tank.y;
	};
	return;
}

bool hit_tank(Tank& tank, Shell& shell) {
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
			if ((x >= 0) && (x + 1 < cols) && (y >= 0) && (y < rows)) {
				if ((map[x][y] > 0) || (map[x + 1][y] > 0)) {
					return true;
				}
			}
			return false;
			break;
		case 1:
			x += Tank_Velocity;
			x = x / 26 + 1;
			y = y / 26;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y + 1 < rows)) {
				if ((map[x][y] > 0) || (map[x][y + 1] > 0)) {
					return true;
				}
			}
			return false;
			break;
		case 2:
			y += Tank_Velocity;
			x = x / 26;
			y = y / 26 + 1;
			if ((x >= 0) && (x + 1 < cols) && (y >= 0) && (y < rows)) {
				if ((map[x][y] > 0) || (map[x + 1][y] > 0)) {
					return true;
				}
			}
			return false;
			break;
		case 3:
			x -= Tank_Velocity;
			x = x / 26;
			y = y / 26;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y + 1 < rows)) {
				if ((map[x][y] > 0) || (map[x][y + 1] > 0)) {
					return true;
				}
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
			if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if (map[x][y] > 0) {
						shell.Exists = false;
						shell.cellX1 = x;
						shell.cellY1 = y;
					}
			}
			if ((x + 1 >= 0) && (x + 1 < cols) && (y >= 0) && (y < rows)) {
				if ((map[x + 1][y] > 0) || (map[x + 1][y] > 0)) {
					shell.Exists = false;
					shell.cellX2 = x + 1;
					shell.cellY2 = y;
				}
			}
			return true;
			break;
		case 1:
			x = x / 26;
			y = y / 26;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if (map[x][y] > 0) {
						shell.Exists = false;
						shell.cellX1 = x;
						shell.cellY1 = y;
					}
			}
			if ((x >= 0) && (x < cols) && (y + 1 >= 0) && (y + 1 < rows)) {
				if ((map[x][y + 1] > 0) || (map[x][y + 1] > 0)) {
					shell.Exists = false;
					shell.cellX2 = x;
					shell.cellY2 = y + 1;
				}
			}
			return true;
			break;
		case 2:
			x = x / 26;
			y = y / 26;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if (map[x][y] > 0) {
						shell.Exists = false;
						shell.cellX1 = x;
						shell.cellY1 = y;
					}
			}
			if ((x + 1 >= 0) && (x + 1 < cols) && (y >= 0) && (y < rows)) {
				if ((map[x + 1][y] > 0) || (map[x + 1][y] > 0)) {
					shell.Exists = false;
					shell.cellX2 = x + 1;
					shell.cellY2 = y;
				}
			}
			return true;
			break;
		case 3:
			x = x / 26;
			y = y / 26;
			if ((x >= 0) && (x < cols) && (y >= 0) && (y < rows)) {
					if (map[x][y] > 0) {
						shell.Exists = false;
						shell.cellX2 = x;
						shell.cellY2 = y;
					}
			}
			if ((x >= 0) && (x < cols) && (y + 1 >= 0) && (y + 1 < rows)) {
				if ((map[x][y + 1] > 0) || (map[x][y + 1] > 0)) {
					shell.Exists = false;
					shell.cellX2 = x;
					shell.cellY2 = y + 1;
				}
			}
			return true;
	};
	return false;
}

bool will_touch(Tank& tank1, Tank& tank2) {
	int dx = tank1.x - tank2.x;
	int dy = tank1.y - tank2.y;
	switch (tank1.id) {
		case 0:
			if ((abs(dx) <= 25) && (dy > 0) && (dy - 50 < Tank_Velocity)) {
				return true;
			}
			return false;
			break;
		case 1:
			if ((abs(dy) <= 25) && (dx < 0) && (dx - 50 > -Tank_Velocity)) {
				return true;
			}
			return false;
			break;
		case 2:
			if ((abs(dx) <= 25) && (dy < 0) && (dy - 50 > -Tank_Velocity)) {
				return true;
			}
			return false;
			break;
		case 3:
			if ((abs(dy) <= 25) && (dx > 0) && (dx - 50 < Tank_Velocity)) {
				return false;
			}
			return false;
	};
	return false;
}

void move_tanks(std::vector<Tank>& Tanks, int** map) {
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

void move_shells(std::vector<Tank>& Tanks) {
	for (int i = 0; i < Tanks.size(); i++) {
		if (Tanks[i].shell.Exists) {
			switch(Tanks[i].shell.side) {
				case 0:
					Tanks[i].shell.y -= Shell_Velocity;
					if (Tanks[i].shell.y <= 0) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 1:
					Tanks[i].shell.x += Shell_Velocity;
					if (Tanks[i].shell.x >= 650) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 2:
					Tanks[i].shell.y += Shell_Velocity;
					if (Tanks[i].shell.y >= 650) {
						Tanks[i].shell.Exists = false;
					}
					break;
				case 3:
					Tanks[i].shell.x -= Shell_Velocity;
					if (Tanks[i].shell.x <= 0) {
						Tanks[i].shell.Exists = false;
					}
			};
		}
	}
}

void move_all(std::vector<Tank>& Tanks, int** map) {
	move_tanks(Tanks, map);
	move_shells(Tanks);
	for (int i = 0; i < Tanks.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (hit_tank(Tanks[i], Tanks[j].shell)) {
			}
		}
		for (int j = i + 1; j < Tanks.size(); j++) {
			if (hit_tank(Tanks[i], Tanks[j].shell)) {
			}
		}
	}
	for (int i = 0; i < Tanks.size(); i++) {
		if (is_in_touch(Tanks[i].shell, map)) {
		}
	}
}





















