#define Tank_Velocity 5
#define Shell_Velocity 10

class Tank {
	public:
		int x;
		int y;
		int side;

		Tank(int posX, int posY) {
			x = posX;
			y = posY;
			side = 0;
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

		void move(int id) {
			if (side != id) {
				align();
			}
			int i = 0;
			switch (id) {
				case 0:
					side = 0;
					while ((y > 0) && (i < Tank_Velocity)) {
						y -= 1;
						i++;
					}
					break;
				case 1:
					side = 1;
					while ((x < 600) && (i < Tank_Velocity)) {
						x += 1;
						i++;
					}
					break;
				case 2:
					side = 2;
					while ((y < 600) && (i < Tank_Velocity)) {
						y += 1;
						i++;
					}
					break;
				case 3:
					side = 3;
					while ((x > 0) && (i < Tank_Velocity)) {
						x -= 1;
						i++;
					}
					break;
				case -1:
					align();
			};
		}


};

class Shell {
	public:
		int x;
		int y;
		int side;

		Shell(int posX, int posY) {
			x = posX;
			y = posY;
			side = 0;
		}

		~Shell() {
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

		void move(int id) {
			if (side != id) {
				align();
			}
			int i = 0;
			switch (id) {
				case 0:
					side = 0;
					while ((y > 0) && (i < Shell_Velocity)) {
						y -= 1;
						i++;
					}
					break;
				case 1:
					side = 1;
					while ((x < 600) && (i < Shell_Velocity)) {
						x += 1;
						i++;
					}
					break;
				case 2:
					side = 2;
					while ((y < 600) && (i < Shell_Velocity)) {
						y += 1;
						i++;
					}
					break;
				case 3:
					side = 3;
					while ((x > 0) && (i < Shell_Velocity)) {
						x -= 1;
						i++;
					}
					break;
				case -1:
					align();
			};
		}


};
