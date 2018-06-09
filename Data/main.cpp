/* CSCI 261 Final Project: Conway's Game Of Life
 *
 * Author: Adam Beziou, Section B
 *
 * Plays Conway's Game of Life, a cellular automata, 0-player game.
 * Allows you to both manually set a board and select from 5 predefined boards.
 */

#include "GameFunctions.h" // For all of the various functions which run the game

#include <iostream> // For cin, cout, cerr, etc.
#include <vector> // For holding the game board of cells
#include <string> // For holding height and width inputs
#include <cstdlib> // For atoi
using namespace std;

#include <SFML\Graphics.hpp> // For drawing 2D shapes
using namespace sf;

int main() {
    const int WIDTH = 500; // Sets the width/height of the window
    const int HEIGHT = 500;
    int gridWidth, gridHeight; // Gets the number of cells in both x/y directions for the game board
    bool manualSet; // Checks if the user wants to manually set the board
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Conway's Game Of Life"); // Creates a render window for drawing to
    Font vtFont; // Creates an object to hold the text font
    
    if (!vtFont.loadFromFile("Font/VT323-Regular.ttf")) { // Atttempts to load the font file
        cerr << "Error loading font..." << endl;
    }
    
    while(window.isOpen()) { // While the window is not closed, repeat
        vector< vector<Cell> > gameBoard; // Holds the cells on the board

        startScreen(window, WIDTH, HEIGHT, vtFont); // Displays the title screen
        manualSet = setGameBoardCells(window, gameBoard, WIDTH, HEIGHT, gridWidth, gridHeight, vtFont); // Prompts the user if they want to manually set the board or not
        if (manualSet) { // If so...
            optionsScreen(window, WIDTH, HEIGHT, gridWidth, gridHeight, vtFont); // Asks them for the height/width of the board
            resizeGameBoard(gameBoard, gridWidth, gridHeight); // Resizes the game board to the user defined width/height
            manuallySetBoard(window, gameBoard, WIDTH, HEIGHT, gridWidth, gridHeight, vtFont); // Allows the user to manually activate cells
        }
        else { // Otherwise...
            pickBoard(window, gameBoard, WIDTH, HEIGHT, vtFont); // Allows the user to pick from a selection of 5 predefined boards
            gridWidth = 50; // Sets the grid width/height to a default of 50
            gridHeight = 50;
        }
        playGame(window, gameBoard, WIDTH, HEIGHT, gridWidth, gridHeight, vtFont); // Allows the player to see the game board evolve and change as generations pass
    }
    
    return 0; // Signlas that the program exited successfully
}