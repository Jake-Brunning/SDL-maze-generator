#pragma once

//each cell is a square
//(x1,y1) = topleft co-ord
//a wall == true means that its solid / exists
//visted == false means the generator hasnt been to that cell yet
class Cell
{
public:
	bool leftWall = true;
	bool upWall = true;
	bool rightWall = true;
	bool downWall = true;
	bool visited = false;
	int x1;
	int y1;
	int width;
	int height;
	Cell(int X1, int Y1, int WIDTH, int HEIGHT) : x1(X1), y1(Y1), width(WIDTH), height(HEIGHT) {

	}
	
private:
	
};

