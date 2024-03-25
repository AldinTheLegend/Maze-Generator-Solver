#pragma once

int main();

struct Cell {
	bool connected;
	bool topWall;
	bool botWall;
	bool rightWall;
	bool leftWall;
	std::pair<int, int> parent;
};
