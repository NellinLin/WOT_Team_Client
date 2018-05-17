#include "project/include/GameProcess.hpp"

int main() {
	while (true) {
		int result = start();
		if (result < 0) {
			return 0;
		}
	}
	return 0;	
}
