#include <math.h>

#define Tank_Velocity 5
#define Shell_Velocity 10

class Shell {
	public:
		int x;
		int y;
		int side;
		bool Exists;

		Shell() {
		}

		~Shell() {
		};
};

class Tank {
	public:
		int x;
		int y;
		int side;
		int hp;

		Tank(int posX, int posY) {
			x = posX;
			y = posY;
			side = 0;
			hp = 2;
		}

		~Tank() {
		};

		void align() {
			if ((x % 25) < 16) {
				x = x - x % 25;
			} else {
				x = x - x % 25 + 25;
			}
			if ((y % 25) < 16) {
				y = y - y % 25;
			} else {
				y = y - y % 25 + 25;
			}
		}
};

void create_shell(Tank& tank, Shell& shell) {
	shell.Exists = true;
	shell.side = tank.side;
	switch (tank.side) {
		case 0:
			shell.x = tank.x + 20;
			shell.y = tank.y;
			break;
		case 1:
			shell.x = tank.x + 50;
			shell.y = tank.y + 20;
			break;
		case 2:
			shell.x = tank.x + 20;
			shell.y = tank.y + 50;
			break;
		case 3:
			shell.x = tank.x;
			shell.y = tank.y + 20;
	};
	if ((shell.x <= 0) || (shell.x >= 650) || (shell.y <= 0) || (shell.y >= 650)) {
		shell.Exists = false;
	}
}

void move_Tanks(Tank& Tank1, int id1, Tank& Tank2, int id2, Shell& shell1, Shell& shell2) {
	int i = 0;
	int dx = Tank1.x - Tank2.x;
	int dy = Tank1.y - Tank2.y;
	switch (id1) {
		case 0:
			if (Tank1.side != id1) {
				Tank1.align();
			}
			Tank1.side = 0;
			while ((Tank1.y > 0) && (i < Tank_Velocity) && !((dy <= 50) && (dy > 0) && (abs(dx) < 50))) {
				Tank1.y -= 1;
				i++;
			}
			break;
		case 1:
			if (Tank1.side != id1) {
				Tank1.align();
			}
			Tank1.side = 1;
			while ((Tank1.x < 600) && (i < Tank_Velocity) && !((dx >= -50) && (dx < 0) && (abs(dy) < 50))) {
				Tank1.x += 1;
				i++;
			}
			break;
		case 2:
			if (Tank1.side != id1) {
				Tank1.align();
			}
			Tank1.side = 2;
			while ((Tank1.y < 600) && (i < Tank_Velocity) && !((dy >= -50) && (dy < 0) && (abs(dx) < 50))) {
				Tank1.y += 1;
				i++;
			}
			break;
		case 3:
			if (Tank1.side != id1) {
				Tank1.align();
			}
			Tank1.side = 3;
			while ((Tank1.x > 0) && (i < Tank_Velocity) && !((dx <= 50) && (dx > 0) && (abs(dy) < 50))) {
				Tank1.x -= 1;
				i++;
			}
			break;
		case 4:
			if (!shell1.Exists) {
				Tank1.align();
			} else {
				create_shell(Tank1, shell1);
			}
			break;
		case -1:
			Tank1.align();
	};
	dx = Tank2.x - Tank1.x;
	dy = Tank2.y - Tank1.y;
	i = 0;
	switch (id2) {
		case 0:
			if (Tank2.side != id2) {
				Tank2.align();
			}
			Tank2.side = 0;
			while ((Tank2.y > 0) && (i < Tank_Velocity) && !((dy <= 50) && (dy > 0) && (abs(dx) < 50))) {
				Tank2.y -= 1;
				i++;
			}
			break;
		case 1:
			if (Tank2.side != id2) {
				Tank2.align();
			}
			Tank2.side = 1;
			while ((Tank2.x < 600) && (i < Tank_Velocity) && !((dx >= -50) && (dx < 0) && (abs(dy) < 50))) {
				Tank2.x += 1;
				i++;
			}
			break;
		case 2:
			if (Tank2.side != id2) {
				Tank2.align();
			}
			Tank2.side = 2;
			while ((Tank2.y < 600) && (i < Tank_Velocity) && !((dy >= -50) && (dy < 0) && (abs(dx) < 50))) {
				Tank2.y += 1;
				i++;
			}
			break;
		case 3:
			if (Tank2.side != id2) {
				Tank2.align();
			}
			Tank2.side = 3;
			while ((Tank2.x > 0) && (i < Tank_Velocity) && !((dx <= 50) && (dx > 0) && (abs(dy) < 50))) {
				Tank2.x -= 1;
				i++;
			}
			break;
		case 4:
			if (shell2.Exists) {
				Tank2.align();
			} else {
				create_shell(Tank2, shell2);
			}
			break;
		case -1:
			Tank2.align();
	};
}

void move_Shell(Shell& shell, Tank& tank) {
	if (!shell.Exists) {
		return;
	}
	int dx = shell.x - tank.x;
	int dy = shell.y - tank.y;
	int i = 0;
	switch (shell.side) {
		case 0:
			while ((shell.y > 0) && (i < Shell_Velocity)) {
				if ((abs(dx) < 50) && (abs(dy) < 50)) {
					tank.hp -= 1;
					shell.Exists = false;
					return;
				}
				shell.y -= 1;
				i += 1;
			}
			if (shell.y <= 0) {
				shell.Exists = false;
			}
			break;
		case 1:
			while ((shell.x < 650) && (i < Shell_Velocity)) {
				if ((abs(dx) < 50) && (abs(dy) < 50)) {
					tank.hp -= 1;
					shell.Exists = false;
					return;
				}
				shell.x += 1;
				i += 1;
			}
			if (shell.x >= 650) {
				shell.Exists = false;
			}
			break;
		case 2:
			while ((shell.y < 650) && (i < Shell_Velocity)) {
				if ((abs(dx) < 50) && (abs(dy) < 50)) {
					tank.hp -= 1;
					shell.Exists = false;
					return;
				}
				shell.y += 1;
				i += 1;
			}
			if (shell.y >= 650) {
				shell.Exists = false;
			}
			break;
		case 3:
			while ((shell.x > 0) && (i < Shell_Velocity)) {
				if ((abs(dx) < 50) && (abs(dy) < 50)) {
					tank.hp -= 1;
					shell.Exists = false;
					return;
				}
				shell.x -= 1;
				i += 1;
			}
			if (shell.x <= 0) {
				shell.Exists = false;
			}
	};
}























