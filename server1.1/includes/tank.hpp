#define step 5

class Tank {
	public:
		int x;
		int y;
		int side;
		int velocity;

		Tank(int posX, int posY, int Side, int vel) {
			x = posX;
			y = posY;
			side = Side;
			velocity = vel;
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
					while ((y > 0) && (i < velocity)) {
						y -= 1;
						i++;
					}
					break;
				case 1:
					side = 1;
					while ((x < 600) && (i < velocity)) {
						x += 1;
						i++;
					}
					break;
				case 2:
					side = 2;
					while ((y < 600) && (i < velocity)) {
						y += 1;
						i++;
					}
					break;
				case 3:
					side = 3;
					while ((x > 0) && (i < velocity)) {
						x -= 1;
						i++;
					}
					break;
				case -1:
					align();
			};
		}


};
