#include <vector>
#include <map>
#include <time.h>
#include <random>
#include <iostream>

#include "ic.hpp"

// Gameboard
#define BOARD_WIDTH 50
#define BOARD_HEIGHT 20
#define BOARD_X 2
#define BOARD_Y 2

std::vector<std::map<short, short>> Snake;
std::map<short, short> Food;

void resetFood(); // Reset the postition of food
void addLength(); // Increase the Snake size by 1
void drawBoard();
void drawSnake();
void drawFood();

void removeFood();
void removeSnake();

void moveSnakeUp();
void moveSnakeDown();
void moveSnakeLeft();
void moveSnakeRight();

void checkSnakeCollision(); // Collision with board or with himself
void Game();

// Directions
bool moveSnakeUp_b = true;
bool moveSnakeDown_b = false;
bool moveSnakeLeft_b = false;
bool moveSnakeRight_b = false;

void setupGame();

int main()
{
	setupGame();
	addLength();
	addLength();

	drawBoard();
	drawFood();
	
	Game();

	getchar();
}

void removeFood()
{
	ic::shorties::gotoxy(::Food.begin()->first, ::Food.begin()->second);
	std::cout << " ";
}

void removeSnake()
{
	for (const auto s : ::Snake)
	{
		ic::shorties::gotoxy(s.begin()->first, s.begin()->second);
		std::cout << " ";
	}
}

void Game()
{
	while (true)
	{
		drawBoard();
		removeSnake();
		if (GetAsyncKeyState(VK_LEFT) && !moveSnakeRight_b)
		{
			if (!moveSnakeLeft_b)
			{	
				moveSnakeLeft();
				drawSnake();
				checkSnakeCollision();
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) && !moveSnakeLeft_b)
		{
			if (!moveSnakeRight_b)
			{
				moveSnakeRight();
				checkSnakeCollision();
			}
		}
		else if (GetAsyncKeyState(VK_UP) && !moveSnakeDown_b)
		{
			if (!moveSnakeUp_b)
			{
				moveSnakeUp();
				checkSnakeCollision();
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) && !moveSnakeUp_b)
		{
			if (!moveSnakeDown_b)
			{
				moveSnakeDown();
				checkSnakeCollision();
			}
		} // Automatic moves
	    else if (moveSnakeDown_b)
		{
			moveSnakeDown();
			checkSnakeCollision();
		}
		else if (moveSnakeUp_b)
		{
			moveSnakeUp();
			checkSnakeCollision();
		}
		else if (moveSnakeRight_b)
		{
			moveSnakeRight();
			checkSnakeCollision();
		}
		else if (moveSnakeLeft_b)
		{
			moveSnakeLeft();
			checkSnakeCollision();
		}

		drawSnake();

		Sleep(100);
	}
}

void checkSnakeCollision()
{
	if (::Snake.begin()->begin()->first == BOARD_X || ::Snake.begin()->begin()->second == BOARD_Y ||
		::Snake.begin()->begin()->first == BOARD_WIDTH || ::Snake.begin()->begin()->second == BOARD_HEIGHT)
	{
		exit(0);
	}
	else if (::Snake.begin()->begin()->first == ::Food.begin()->first &&
			 ::Snake.begin()->begin()->second == ::Food.begin()->second)
	{
		addLength();
		removeFood();
		resetFood();
		drawFood();
	}
	else
	{
		bool first = true;
		std::vector<std::map<short, short>>::iterator it = Snake.begin();
		for (const auto s : Snake)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				if (s.begin()->first == it->begin()->first &&
					s.begin()->second == it->begin()->second)
				{
					exit(0);
				}
			}
		}
	}
}

void moveSnakeRight()
{
	if (!moveSnakeRight_b)
	{
		moveSnakeUp_b = false;
		moveSnakeDown_b = false;
		moveSnakeLeft_b = false;
		moveSnakeRight_b = true;
	}

	short tempX, tempY;
	short temp2X, temp2Y;
	bool first = true;

	short operation = 1;

	for (auto& s : ::Snake)
	{
		if (first)
		{
			tempX = s.begin()->first;
			tempY = s.begin()->second;
			::Snake.begin()->clear();
			::Snake.begin()->insert({ tempX + 1, tempY });
			first = false;
		}
		else
		{
			if (operation == 1)
			{
				temp2X = s.begin()->first;
				temp2Y = s.begin()->second;

				s.clear();
				s.insert({ tempX, tempY });
				operation = -1;
			}
			else if (operation == -1)
			{
				tempX = s.begin()->first;
				tempY = s.begin()->second;

				s.clear();
				s.insert({ temp2X, temp2Y });
				operation = 1;
			}
		}
	}
}

void moveSnakeLeft()
{
	if (!moveSnakeLeft_b)
	{
		moveSnakeUp_b = false;
		moveSnakeDown_b = false;
		moveSnakeLeft_b = true;
		moveSnakeRight_b = false;
	}

	short tempX, tempY;
	short temp2X, temp2Y;
	bool first = true;

	short operation = 1;

	for (auto& s : ::Snake)
	{
		if (first)
		{
			tempX = s.begin()->first;
			tempY = s.begin()->second;
			::Snake.begin()->clear();
			::Snake.begin()->insert({ tempX - 1, tempY });
			first = false;
		}
		else
		{
			if (operation == 1)
			{
				temp2X = s.begin()->first;
				temp2Y = s.begin()->second;

				s.clear();
				s.insert({ tempX, tempY });
				operation = -1;
			}
			else if (operation == -1)
			{
				tempX = s.begin()->first;
				tempY = s.begin()->second;

				s.clear();
				s.insert({ temp2X, temp2Y });
				operation = 1;
			}
		}
	}
}

void moveSnakeDown()
{

	if (!moveSnakeDown_b)
	{
		moveSnakeUp_b = false;
		moveSnakeDown_b = true;
		moveSnakeLeft_b = false;
		moveSnakeRight_b = false;
	}

	short tempX, tempY;
	short temp2X, temp2Y;
	bool first = true;

	short operation = 1;

	for (auto& s : ::Snake)
	{
		if (first)
		{
			tempX = s.begin()->first;
			tempY = s.begin()->second;
			s.begin()->second += 1;
			first = false;
		}
		else
		{
			if (operation == 1)
			{
				temp2X = s.begin()->first;
				temp2Y = s.begin()->second;

				s.clear();
				s.insert({ tempX, tempY });
				operation = -1;
			}
			else if (operation == -1)
			{
				tempX = s.begin()->first;
				tempY = s.begin()->second;

				s.clear();
				s.insert({ temp2X, temp2Y });
				operation = 1;
			}
		}
	}
}

void moveSnakeUp()
{
	if (!moveSnakeUp_b)
	{
		moveSnakeUp_b = true;
		moveSnakeDown_b = false;
		moveSnakeLeft_b = false;
		moveSnakeRight_b = false;
	}

	short tempX, tempY;
	short temp2X, temp2Y;
	bool first = true;

	short operation = 1;

	for (auto& s : ::Snake)
	{
		if (first)
		{
			tempX = s.begin()->first;
			tempY = s.begin()->second;
			s.begin()->second -= 1;
			first = false;
		}
		else
		{
			if (operation == 1)
			{
				temp2X = s.begin()->first;
				temp2Y = s.begin()->second;

				s.clear();
				s.insert({ tempX, tempY });
				operation = -1;
			}
			else if (operation == -1)
			{
				tempX = s.begin()->first;
				tempY = s.begin()->second;

				s.clear();
				s.insert({ temp2X, temp2Y });
				operation = 1;
			}
		}
	}
}

void drawFood()
{
	ic::shorties::gotoxy(::Food.begin()->first, ::Food.begin()->second);
	std::cout << "?";
}


void setupGame()
{
	short x, y;
	x = (BOARD_WIDTH /2);
	y = (BOARD_HEIGHT /2);
	std::map<short, short> pos;
	pos.insert({ x, y });
	Snake.push_back(pos);

	resetFood();
}

void drawSnake()
{
	for (const auto& s : ::Snake)
	{
		for (const auto& s_pos : s)
		{
			ic::shorties::gotoxy(s_pos.first, s_pos.second);
			std::cout << "O";
		}
	}
}

void addLength()
{
	short x, y;
	x = y = 0;

	if (moveSnakeUp_b)
	{
		std::vector<std::map<short, short>>::iterator it = Snake.end();
		--it;

		x = it->begin()->first;
		y = it->begin()->second + 1;
		
		std::map<short, short> pos;
		pos.insert({ x, y });
		::Snake.push_back(pos);
	}
	else if (moveSnakeDown_b)
	{
		std::vector<std::map<short, short>>::iterator it = Snake.end();
		--it;

		x = it->begin()->first;
		y = it->begin()->second - 1;

		std::map<short, short> pos;
		pos.insert({ x, y });
		::Snake.push_back(pos);
	}
	else if (moveSnakeLeft_b)
	{
		std::vector<std::map<short, short>>::iterator it = Snake.end();
		--it;

		x = it->begin()->first + 1;
		y = it->begin()->second;

		std::map<short, short> pos;
		pos.insert({ x, y });
		::Snake.push_back(pos);
	}
	else if (moveSnakeRight_b)
	{
		std::vector<std::map<short, short>>::iterator it = Snake.end();
		--it;

		x = it->begin()->first - 1;
		y = it->begin()->second;

		std::map<short, short> pos;
		pos.insert({ x, y });
		::Snake.push_back(pos);
	}
}

void resetFood()
{
	short x, y;

	std::default_random_engine generator(clock());
	std::uniform_int_distribution<short> distributionX((BOARD_X + 1), (BOARD_WIDTH - 1));
	std::uniform_int_distribution<short> distributionY((BOARD_Y + 1), (BOARD_HEIGHT - 1));

	x = distributionX(generator);
	y = distributionY(generator);

	::Food.clear();
	::Food.insert({ x, y });
}

void drawBoard()
{
	// Draw upper line
	for (short i = BOARD_X; i < BOARD_WIDTH; ++i)
	{
		ic::shorties::gotoxy(i, BOARD_Y);
		std::cout << "#";
	}

	// Draw lower line
	for (short i = BOARD_X; i < BOARD_WIDTH; ++i)
	{
		ic::shorties::gotoxy(i, BOARD_HEIGHT);
		std::cout << "#";
	}

	// Draw left line
	for (short i = BOARD_Y; i < BOARD_HEIGHT; ++i)
	{
		ic::shorties::gotoxy(BOARD_X, i);
		std::cout << "#";
	}

	// Draw right line
	for (short i = BOARD_Y; i <= BOARD_HEIGHT; ++i)
	{
		ic::shorties::gotoxy(BOARD_WIDTH, i);
		std::cout << "#";
	}
}
