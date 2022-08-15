#include <SDL.h>
#include <stdio.h>
#include <iostream>;
#include <cstdlib>
#include "Framework.h";
#include "Stack.h";
#include "Cell.h";
#include "Cordinates.h";

const int width = 1720;
const int height = 920;
const int amountOfCellsX = 20;
const int amountOfCellsY = 10;


Cell* cells[amountOfCellsX][amountOfCellsY];
Framework fw(width + 5, height + 5);

Cordinates getStartCordinates(bool endCord = false, int startWall = 0) {

	int wall = rand() % 4; //what wall, 0 == top, 1 == right, 2 == down, 3 == left
	int X = 0; //to return
	int Y = 0; //to return
	if (endCord) {
		wall = startWall;
	}
	//assign start cell base on what wall was selected
	switch (wall)
	{
	case 0:
		X = rand() % amountOfCellsX;
		cells[X][Y]->upWall = false;
		break;
	case 1:
		X = amountOfCellsX - 1;
		Y = rand() % amountOfCellsY;
		cells[X][Y]->rightWall = false;
		break;
	case 2:
		Y = amountOfCellsY - 1;
		X = rand() % amountOfCellsX;
		cells[X][Y]->downWall = false;
		break;
	case 3:
		Y = rand() % amountOfCellsY;
		cells[X][Y]->leftWall = false;
		break;
	default:
		break;
	}

	return Cordinates(X, Y);
}

bool CanMoveToCell(Cordinates cordinates, int direction, bool playerOrGenerator = false) {
	//if a cell has not been visited and is not off the cell grid then return true. Else return false
	//0: top, 1: right, 2: down, 3: left
	
	if (direction == 0 && cordinates.y - 1 >= 0 && cells[cordinates.x][cordinates.y - 1]->visited == false) {
		return true;
	}
	else if (direction == 1 && cordinates.x + 1 < amountOfCellsX && cells[cordinates.x + 1][cordinates.y]->visited == false) {
		return true;
	}
	else if (direction == 2 && cordinates.y + 1 < amountOfCellsY && cells[cordinates.x][cordinates.y + 1]->visited == false) {
		return true;
	}
	else if (direction == 3 && cordinates.x - 1 >= 0 && cells[cordinates.x - 1][cordinates.y]->visited == false) {
		return true;
	}
	
	return false;
}

void drawGrid() { //draw the cell grid
	for (int i = 0; i < amountOfCellsX; i++) {
		for (int j = 0; j < amountOfCellsY; j++) {
			fw.drawCellgrid(cells[i][j]);
		}
	}
}


void RecursiveGenerate(Cordinates currentCellCorords) {
	cells[currentCellCorords.x][currentCellCorords.y]->visited = true; //set the cell were on as visited
	fw.Clear();
	SDL_Delay(25);

	while (true) //once count equal to 4 all options around the cell has been used
	{
		//If no moves are possible return, essentially going back to the last cell and checking the same thing
		if (CanMoveToCell(currentCellCorords, 0) == false && CanMoveToCell(currentCellCorords, 1) == false && CanMoveToCell(currentCellCorords, 2) == false && CanMoveToCell(currentCellCorords, 3) == false) {
			return;
		}

		int direction = rand() % 4; //0: top, 1: right, 2: down, 3: left
		if (CanMoveToCell(currentCellCorords, direction)) //if a move is possible
		{
			switch (direction)
			{
			case 0:
				cells[currentCellCorords.x][currentCellCorords.y]->upWall = false; //braking wall
				cells[currentCellCorords.x][currentCellCorords.y - 1]->downWall = false; //braking wall of other cell
				drawGrid();
				fw.render();
				RecursiveGenerate(Cordinates(currentCellCorords.x, currentCellCorords.y - 1)); //repeat process with the cell needed
				break;
			case 1:
				cells[currentCellCorords.x][currentCellCorords.y]->rightWall = false;
				cells[currentCellCorords.x + 1][currentCellCorords.y]->leftWall = false;
				drawGrid();
				fw.render();
				RecursiveGenerate(Cordinates(currentCellCorords.x + 1, currentCellCorords.y));
				break;
			case 2:
				cells[currentCellCorords.x][currentCellCorords.y]->downWall = false;
				cells[currentCellCorords.x][currentCellCorords.y + 1]->upWall = false;
				drawGrid();
				fw.render();
				RecursiveGenerate(Cordinates(currentCellCorords.x, currentCellCorords.y + 1));
				break;
			case 3:
				cells[currentCellCorords.x][currentCellCorords.y]->leftWall = false;
				cells[currentCellCorords.x - 1][currentCellCorords.y]->rightWall = false;
				drawGrid();
				fw.render();
				RecursiveGenerate(Cordinates(currentCellCorords.x - 1, currentCellCorords.y));
				break;
			}
		}
		
	}
}

bool checkIfPlayerCanMove(Cordinates current, int direction) {
	switch (direction) {
	case 0:
		if (cells[current.x][current.y]->upWall == false) {
			return true;
		}
		break;
	case 1:
		if (cells[current.x][current.y]->rightWall == false) {
			return true;
		}
		break;
	case 2:
		if (cells[current.x][current.y]->downWall == false) {
			return true;
		}
		break;
	case 3:
		if (cells[current.x][current.y]->leftWall == false) {
			return true;
		}
		break;
	}
	return false;
}


int main(int argc, char* args[]) {

	//cell width and height based on how big the screen is
	const int cellWidth = width / amountOfCellsX;
	const int cellHeight = height / amountOfCellsY;

	//initilise values for cells and draw them to the screen
	for (int i = 0; i < amountOfCellsX; i++) {
		for (int j = 0; j < amountOfCellsY; j++) {
			cells[i][j] = new Cell(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			fw.drawCellgrid(cells[i][j]);
			fw.render();
		}
	}
	//generate start and end point
	srand(time(0));
	Cordinates start = getStartCordinates();
	//start recursiveDepthSearch
	RecursiveGenerate(start);

	//generate the end cordinate on the other side of the maze
	//figures out which wall the start is on by using co-ords of said start 
	//then adjusts so its generated on the right wall
	Cordinates end;
	if (start.x == 0) {
		end = getStartCordinates(true, 1);
	}
	else if (start.x == amountOfCellsX - 1) {
		end = getStartCordinates(true, 3);
	}
	else if (start.y == 0) {
		end = getStartCordinates(true, 2);
	}
	else if (start.y == amountOfCellsY - 1) {
		end = getStartCordinates(true, 0);
	}
	drawGrid();
	fw.render();
	std::vector<Cell*> cellSnake = {cells[start.x][start.y]};
	Cordinates current = start; //the cell the player is currently on
	
	//gaming loop
	const int frameDelay = 10;
	int frametime;
	int framestart;
	SDL_Event event{};


	while (true) {
		framestart = SDL_GetTicks();
		fw.Clear();
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_w:
					std::cout << "keypress detected " << std::endl;
					if (checkIfPlayerCanMove(current, 0)) {
						current.y--;
						cellSnake.push_back(cells[current.x][current.y]);
						SDL_FlushEvent(SDLK_w);
					}
					break;

				case SDLK_a:
					if (checkIfPlayerCanMove(current, 3)) {
						current.x--;
						cellSnake.push_back(cells[current.x][current.y]);
					}
					break;

				case SDLK_d:
					if (checkIfPlayerCanMove(current, 1)) {
						current.x++;
						cellSnake.push_back(cells[current.x][current.y]);
						SDL_FlushEvent(SDLK_d);
					}
					break;

				case SDLK_s:
					if (checkIfPlayerCanMove(current, 2)) {
						current.y++;
						cellSnake.push_back(cells[current.x][current.y]);
						SDL_FlushEvent(SDLK_s);
					}
					break;
				}
			break;
			case SDL_QUIT:
				return 2;
				break;
		}


		for (int i = 0; i < cellSnake.size(); i++) { //draw the cell snake
			fw.DrawCell(cellSnake.at(i));
		}
		drawGrid();
		fw.DrawCell(cells[current.x][current.y], 255, 255);
		fw.render();
		frametime = SDL_GetTicks() - framestart;
		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
			
		}
		
		SDL_PollEvent(&event);
	}
	return 0;
}