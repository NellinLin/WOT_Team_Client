# Для компиляции :
   g++ -c main.cpp && g++ main.o -o main.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network && ./main.out


# Графика от Темера:
   * ACHTUNG!
	В окне "window" начало отсчета в левом ВЕРХНЕМ углу.
	Положительное направление оси OY направлено ВНИЗ.
	Положительное направление оси OX направлено Вправо.

   myGraphics.hpp - описание..
   * class myTexture:
	1) myTexture(std::string filepath) {}
		Инициализация (filepath - путь к картинке).

	2) void setPossition(sf::RenderWindow &window, int x, int y) {}
		Устанавливает текстуру на пиксель (x, y).

	3) void move(sf::RenderWindow &window, int x, int y) {}
		Двигает текстурку и принтит новое состояние.

	4) void draw(sf::RenderWindow &window, int x, int y) {}
		Помещает текстуру на пиксель (x, y) и принтит ее.

	5) void draw(sf::RenderWindow &window) {}
		Просто принтит картинку в текущем состоянии.

	6) int isPressed(sf::RenderWindow & window) {}
		Проверяет, нажал ли пользователь на текстурку левой. кнопкой мыши
   * int key_id() {}
	выводит id нажатой клавишы
		1 - Up,
		2 - Right,
		3 - Down,
		4 - Left.
