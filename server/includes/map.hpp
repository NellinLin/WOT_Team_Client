#include <iostream>
#include <fstream>

#define ERR_F NULL

int** Read_from_file(const char *f) {
	std::fstream file(f);
	if (!file.is_open())
		return ERR_F;
	int rows = 0, cols = 0;
	file >> rows >> cols;
	int ** map;
	map = new int*[rows];
	for (int i = 0; i < rows; i++) map[i] = new int[cols];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			map[i][j] = 0;
	}

	int buf1, buf2, buf3;
	while (!file.eof()) {
		file >> buf1 >> buf2 >> buf3;
		map[buf1][buf2] = buf3;
	}
	file.close();
	return map;
}
