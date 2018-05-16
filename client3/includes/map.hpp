#include <iostream>
#include <fstream>

#define ERR_F NULL
#define rows 26
#define cols 26

int** Read_from_file(const char *f) {
	std::fstream file(f);
	if (!file.is_open()) {
		return ERR_F;
	}
	int** map;
	map = new int*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			map[i][j] = -1;
	}
	int buf1, buf2, buf3;
	while (!file.eof()) {
		file >> buf1 >> buf2 >> buf3;
		if ((buf1 >= 0) && (buf1 < rows) && (buf2 >= 0) && (buf2 < cols)) {
			map[buf1][buf2] = buf3;
		}
	}
	file.close();
	return map;
}
