#include "Cell.h" // For the cell class

#include <vector> // USed for holding the game board of cells
using namespace std;

Cell::Cell() { // Default constructor
    _xPos = 0;
    _yPos = 0;
    _state = false;
}

Cell::Cell(int xPos, int yPos, bool state) { // Overloaded constructor
    _xPos = xPos;
    _yPos = yPos;
    _state = state;
}

int Cell::getXPos() { // Getters
    return _xPos;
}
int Cell::getYPos() {
    return _yPos;
}
int Cell::getNumNeighbors() {
    return _numNeighbors;
}
bool Cell::getState() {
    return _state;
}

void Cell::setXPos(int xPos) { // Setters
    _xPos = xPos;
}
void Cell::setYPos(int yPos) {
    _yPos = yPos;
}
void Cell::setState(bool state) {
    _state = state;
}
void Cell::setNumNeighbors(int numNeighbors) {
    _numNeighbors = numNeighbors;
}
