#pragma once

#include "Cell.h" // For the cell class

#include <iostream> // For cin, cout, cerr, etc.
#include <vector> // For holding the game board of cells
#include <string> // For holding height and width inputs
#include <cstdlib> // For atoi
using namespace std;

#include <SFML\Graphics.hpp> // For RenderWindow, Font, etc.
using namespace sf;

int startScreen(RenderWindow& window, const int WIDTH, const int HEIGHT, Font vtFont); // Displays the title screen

void optionsScreen(RenderWindow& window, const int WIDTH, const int HEIGHT, int& gridWidth, int& gridHeight, Font vtFont); // Displays the height/width prompt

void resizeGameBoard(vector< vector<Cell> >& gameBoard, int gridWidth, int gridHeight); // Resizes the game board to the desired size

void displayGameBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight); // Displays the game board grid and any active cells

void advanceGeneration(vector< vector<Cell> >& gameBoard); // Advances the cell generation, according to a set of rules

void pickBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, Font vtFont); // Displays the options for pickking a predefined board of cells

void manuallySetBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont); // Displays a grid for manually activating cells

bool setGameBoardCells(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont); // Displays the prompt for wither manually setting cells or picking a predefined board

void playGame(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont); // Displays the game board as generations advance