#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <thread>

#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "Rendering.h"

const int HEIGHT = 8;
const int WIDTH = 8;
const int TOTAL_CELLS = WIDTH * HEIGHT;
const std::pair<int, int> ENTRENCE = std::make_pair(0, 0);
const std::pair<int, int> EXIT = std::make_pair(WIDTH - 1, HEIGHT - 1);

int randomGenerator(int MIN, int MAX)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(MIN, MAX);

	int random_number = dis(gen);

	return random_number;
}

void renderMaze(std::vector<std::vector<Cell>>& maze, int color)
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			draw(maze, i, j, color);
		}
	}
}

void removeWalls(std::vector<std::vector<Cell>>& maze, int prevX, int prevY, int currentX, int currentY)
{
	if (prevX < currentX || prevX > currentX)
	{
		if (prevX < currentX)
		{
			maze[currentX][currentY].leftWall = false;
			maze[prevX][currentY].rightWall = false;
		}
		else
		{
			maze[currentX][currentY].rightWall = false;
			maze[prevX][currentY].leftWall = false;
		}
	}
	else if (prevY < currentY || prevY > currentY)
	{
		if (prevY < currentY)
		{
			maze[currentX][currentY].topWall = false;
			maze[currentX][prevY].botWall = false;
		}
		else
		{
			maze[currentX][currentY].botWall = false;
			maze[currentX][prevY].topWall = false;
		}
	}
}

void findFrontiers(std::vector<std::vector<Cell>>& maze, std::vector<std::pair<int, int>>& frontiers, int& neighbors, int currentX, int currentY)
{
	if (currentX > 0 && !maze[currentX - 1][currentY].connected)
	{
		frontiers.push_back(std::make_pair(currentX - 1, currentY));
		neighbors += 1;
	}
	if (currentX < WIDTH - 1 && !maze[currentX + 1][currentY].connected)
	{
		frontiers.push_back(std::make_pair(currentX + 1, currentY));
		neighbors += 1;
	}
	if (currentY > 0 && !maze[currentX][currentY - 1].connected)
	{
		frontiers.push_back(std::make_pair(currentX, currentY - 1));
		neighbors += 1;
	}
	if (currentY < HEIGHT - 1 && !maze[currentX][currentY + 1].connected)
	{
		frontiers.push_back(std::make_pair(currentX, currentY + 1));
		neighbors += 1;
	}
}



void mazeGeneration(std::vector<std::vector<Cell>>& maze, int color)
{
	int currentX = randomGenerator(0, WIDTH - 1);
	int currentY = randomGenerator(0, HEIGHT - 1);

	std::vector<std::pair<int, int>> connectedCells;
	while (true)
	{
		std::vector<std::pair<int, int>> frontiers;
		int neighbors = 0;

		findFrontiers(maze, frontiers, neighbors, currentX, currentY);

		int prevX = currentX;
		int prevY = currentY;

		if (neighbors == 0) {
			while (connectedCells.size() != TOTAL_CELLS)
			{
				std::pair<int, int> randConnected = connectedCells[randomGenerator(0, connectedCells.size() - 1)];
				findFrontiers(maze, frontiers, neighbors, randConnected.first, randConnected.second);

				if (neighbors != 0) {
					int rand = randomGenerator(1, neighbors);
					std::pair<int, int> nextCell = frontiers[rand - 1];

					currentX = nextCell.first;
					currentY = nextCell.second;
					removeWalls(maze, randConnected.first, randConnected.second, currentX, currentY);
					draw(maze, randConnected.first, randConnected.second, color);
					draw(maze, currentX, currentY, color);
					break;
				}
			}
			if (connectedCells.size() == TOTAL_CELLS)
				break;
		}
		else
		{
			int rand = randomGenerator(1, neighbors);

			std::pair<int, int> nextCell = frontiers[rand - 1];
			currentX = nextCell.first;
			currentY = nextCell.second;

			removeWalls(maze, prevX, prevY, currentX, currentY);
			draw(maze, prevX, prevY, color);
			draw(maze, currentX, currentY, color);
		}
		maze[currentX][currentY].connected = true;
		connectedCells.push_back(std::make_pair(currentX, currentY));

	}

	maze[ENTRENCE.first][ENTRENCE.second].topWall = false;
	maze[EXIT.first][EXIT.second].botWall = false;
	draw(maze, ENTRENCE.first, ENTRENCE.second, color);
	draw(maze, EXIT.first, EXIT.second, color);
	//renderMaze(maze);
}

void initializeMaze(std::vector<std::vector<Cell>>& maze, int color)
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			maze[i][j] = { false, true, true, true, true };
		}
	}
	renderMaze(maze, color);
	mazeGeneration(maze, color);
}

int main()
{
	int color = 7;
	std::vector<std::vector<Cell>> maze(WIDTH, std::vector<Cell>(HEIGHT));;
	initializeMaze(maze, color);

	bredthFirstSearch(maze, ENTRENCE, EXIT);
}

