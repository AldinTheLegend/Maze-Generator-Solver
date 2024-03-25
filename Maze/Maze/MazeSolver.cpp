#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <thread>

#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "Rendering.h"

bool hasBeenVisited(std::vector<std::pair<int, int>> visited, std::pair<int, int> currentPos) {
	for (int i = 0; i < visited.size(); ++i) {
		if (currentPos == visited[i])
			return true;
	}
	return false;
}

void findAvailableNeighbors(std::vector<std::vector<Cell>>& maze, std::pair<int, int> currentPos, std::pair<int, int>& prevPos, std::vector<std::pair<int, int>>& queue, std::vector<std::pair<int, int>>& visited)
{
	if (!maze[currentPos.first][currentPos.second].rightWall && !hasBeenVisited(visited, std::make_pair(currentPos.first + 1, currentPos.second))) {
		queue.push_back(std::make_pair(currentPos.first + 1, currentPos.second));
		maze[currentPos.first + 1][currentPos.second].parent = currentPos;
	}
	if (!maze[currentPos.first][currentPos.second].leftWall && !hasBeenVisited(visited, std::make_pair(currentPos.first - 1, currentPos.second))) {
		queue.push_back(std::make_pair(currentPos.first - 1, currentPos.second));
		maze[currentPos.first - 1][currentPos.second].parent = currentPos;
	}
	if (!maze[currentPos.first][currentPos.second].topWall && currentPos != std::make_pair(0, 0) && !hasBeenVisited(visited, std::make_pair(currentPos.first, currentPos.second - 1))) {
		queue.push_back(std::make_pair(currentPos.first, currentPos.second - 1));
		maze[currentPos.first][currentPos.second - 1].parent = currentPos;
	}
	if (!maze[currentPos.first][currentPos.second].botWall && !hasBeenVisited(visited, std::make_pair(currentPos.first, currentPos.second + 1))) {
		queue.push_back(std::make_pair(currentPos.first, currentPos.second + 1));
		maze[currentPos.first][currentPos.second + 1].parent = currentPos;
	}
}

void bredthFirstSearch(std::vector<std::vector<Cell>>& maze, const std::pair<int, int>& entrence, const std::pair<int, int>& exit)
{
	int color = 20;

	std::vector<std::pair<int, int>> queue; //
	std::vector<std::pair<int, int>> visited; //(0,0) 

	std::pair<int, int> prevPos;
	std::pair<int, int> currentPos = entrence;

	while (currentPos != exit)
	{
		visited.push_back(currentPos);
		findAvailableNeighbors(maze, currentPos, prevPos, queue, visited);
		prevPos = currentPos;
		currentPos = queue.front();
		queue.erase(queue.begin());
		draw(maze, currentPos.first, currentPos.second, color);
	}
	std::cout << "exit reached at: " << currentPos.first << currentPos.second;

	color = 40;
	while (currentPos != entrence) {
		draw(maze, currentPos.first, currentPos.second, color);
		currentPos = maze[currentPos.first][currentPos.second].parent;
	}
	draw(maze, currentPos.first, currentPos.second, color);
}
