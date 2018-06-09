#include <vector> // USed for holding the game board of cells
using namespace std;

class Cell { // Creates the cell class
    public:
        Cell(); // Default constructor
        Cell(int xPos, int yPos, bool state); // Overloaded constructor
        int getXPos(); // Getters
        int getYPos();
        bool getState();
        int getNumNeighbors();
        
        void setXPos(int xPos); // Setters
        void setYPos(int yPos);
        void setState(bool state);
        void setNumNeighbors(int numNeighbors);
    private:
        int _numNeighbors; // Holds the number of neighboring active cells
        int _xPos; // Holds the x position of the cell
        int _yPos; // Holds the y position of the cell
        bool _state; // Holds the state (alive/dead) of a cell
};