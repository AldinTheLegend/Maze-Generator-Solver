#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <thread>

#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "Rendering.h"

int setY(int i)
{
	return (i * 3);
}
int setX(int j)
{
	return (j * 5);
}

void topDraw(const std::vector<std::vector<Cell>>& maze, HANDLE hConsole, int currentX, int currentY, int color)
{

	std::cout << "+";
	if (!maze[currentX][currentY].topWall) {
		SetConsoleTextAttribute(hConsole, color);
		std::cout << ("   ");
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << ("---");
	}

	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "+";
}

void botDraw(const std::vector<std::vector<Cell>>& maze, HANDLE hConsole, int currentX, int currentY, int color)
{
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "+";
	if (!maze[currentX][currentY].botWall) {
		SetConsoleTextAttribute(hConsole, color);
		std::cout << ("   ");
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << ("---");
	}
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "+";
}

void leftDraw(const std::vector<std::vector<Cell>>& maze, HANDLE hConsole, int currentX, int currentY, int color) {
	if (!maze[currentX][currentY].leftWall) {
		SetConsoleTextAttribute(hConsole, color);
		std::cout << " ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "|";
	}
	SetConsoleTextAttribute(hConsole, 7);
}
void rightDraw(const std::vector<std::vector<Cell>>& maze, HANDLE hConsole, int currentX, int currentY, int color) {
	if (!maze[currentX][currentY].rightWall) {
		SetConsoleTextAttribute(hConsole, color);
		std::cout << " ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "|";
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void lastDraw(int endX, int endY) {
	int x = setX(endX);
	int y = setY(endY + 3);
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw(const std::vector<std::vector<Cell>>& maze, int currentX, int currentY, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int Y = setY(currentY);
	int X = setX(currentX);
	COORD pos = { X, Y };

	SetConsoleCursorPosition(hConsole, pos);
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	topDraw(maze, hConsole, currentX, currentY, color);

	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	pos.Y += 1;
	SetConsoleCursorPosition(hConsole, pos);
	leftDraw(maze, hConsole, currentX, currentY, color);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << "   ";  // Print content of the cell here
	SetConsoleTextAttribute(hConsole, 7);
	rightDraw(maze, hConsole, currentX, currentY, color);
	SetConsoleTextAttribute(hConsole, color);

	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	pos.Y += 1;
	SetConsoleCursorPosition(hConsole, pos);
	botDraw(maze, hConsole, currentX, currentY, color);

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}