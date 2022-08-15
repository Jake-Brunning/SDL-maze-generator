#pragma once
#include <SDL.h>
#include <iostream>;
#include "Cell.h";
class Framework {
public:
	Framework(int width_, int height_) : height(height_), width(width_) {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		}

		window = SDL_CreateWindow("SDL Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, 0, SDL_WINDOW_SHOWN);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	~Framework() { //deconstructor to properly get rid of framework
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	void DrawCell(Cell* cell, int r = 0, int g = 0, int b = 255) {
		SDL_Rect* rect = new SDL_Rect();
		rect->x = cell->x1;
		rect->y = cell->y1;
		rect->w = cell->width;
		rect->h = cell->height;
		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_RenderFillRect(renderer, rect);
	}
	

	void drawCellgrid(Cell* current) { //draws the outline around a cell with by drawing lines 
		
		if (current->upWall == true) {
			drawline(current->x1, current->y1, current->x1 + current->width, current->y1);
		}
		if (current->rightWall == true) {
			drawline(current->x1 + current->width, current->y1, current->x1 + current->width, current->y1 + current->height);
		}
		if (current->downWall == true) {
			drawline(current->x1, current->y1 + current->height, current->x1 + current->width, current->y1 + current->height);
		}
		if (current->leftWall == true) {
			drawline(current->x1, current->y1, current->x1, current->y1 + current->height);
		}
	}

	void drawline(int x1, int y1, int x2, int y2, int r = 0, int g = 255, int b = 0) {
		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}

	void Clear(int r = 0, int g = 0, int b = 0) {
		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_RenderClear(renderer);
	}
	void render() {
		SDL_RenderPresent(renderer);
	}
	int GetHeight() {
		return height;
	}
	int GetWidth() {
		return width;
	}
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int height;
	int width;
};

