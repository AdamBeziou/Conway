#include "GameFunctions.h"

#include <iostream> // For cin, cout, cerr, etc.
#include <vector> // For holding the game board of cells
#include <string> // For holding height and width inputs
#include <cstdlib> // For atoi
using namespace std;

#include <SFML\Graphics.hpp> // For RenderWindow, Font, etc.
using namespace sf;

int startScreen(RenderWindow& window, const int WIDTH, const int HEIGHT, Font vtFont) {  // Displays the title screen
    Text title, startOption, quitOption; // Holds text boxes
    RectangleShape bar; // Shape for the grid bars
    Event event; // Keeps track of events
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        /* Drawing Title */
        title.setFont(vtFont); // Sets font
        title.setString("Conway's Game of Life"); // Sets the string displayed in the text box
        title.setCharacterSize(50);
        title.setColor(Color(142, 145, 150)); // Sets the color to be a slightly light grey
        FloatRect titleRectangle = title.getLocalBounds(); // Gets the bounding box of the text box
        title.setOrigin(titleRectangle.left + titleRectangle.width / 2.0, titleRectangle.top + titleRectangle.height / 2.0); // Sets the origin in the center of the box
        title.setPosition(Vector2f(WIDTH / 2.0, titleRectangle.height)); // Centers the box
        
        window.draw(title); // Draws the title dropshadow
        
        title.setColor(Color::White); // Makes the color white
        title.setPosition(Vector2f(WIDTH / 2.0, titleRectangle.height + 2)); // Moves the box down slightly
        
        window.draw(title); // Draws the foreground title
        
        /* Drawing Start/Stop Option */
        startOption.setFont(vtFont); // Sets attributes
        quitOption.setFont(vtFont);
        startOption.setString("Press ENTER to Start");
        quitOption.setString("Press ESC to Quit");
        startOption.setCharacterSize(40);
        quitOption.setCharacterSize(40);
        startOption.setColor(Color::White);
        quitOption.setColor(Color::White);
        FloatRect startOptionRectangle = startOption.getLocalBounds(); // Centers both text boxes
        FloatRect quitOptionRectangle = quitOption.getLocalBounds();
        startOption.setOrigin(startOptionRectangle.left + startOptionRectangle.width / 2.0, startOptionRectangle.top + startOptionRectangle.height / 2.0);
        quitOption.setOrigin(quitOptionRectangle.left + quitOptionRectangle.width / 2.0, quitOptionRectangle.top + quitOptionRectangle.height / 2.0);
        startOption.setPosition(Vector2f(WIDTH / 2.0, titleRectangle.height + 2 + startOptionRectangle.height * 2));
        quitOption.setPosition(Vector2f(WIDTH / 2.0, titleRectangle.height + 2 + startOptionRectangle.height * 2 + quitOptionRectangle.height * 2));
        
        window.draw(startOption); // Draws both boxes
        window.draw(quitOption);
        
        /* Drawing Bottom Cell Grid */
        double barXPos = 0, barYPos = HEIGHT, barWidth = WIDTH / 250.0, barHeight = 300.0; // Sets the attributes for the grid bars; sets bar width to be approx 2 pixels
        bar.setSize(Vector2f(barWidth, barHeight));
        bar.setPosition(Vector2f(barXPos, HEIGHT - barHeight));
        bar.setFillColor(Color(54, 54, 56));
        
        for (int i = 0; i < (int) WIDTH / (barWidth * 5); i++) { // Draws horizontal bars, with each bar being spaced 5 bar widths apart
            window.draw(bar);
            barXPos += barWidth * 5;
            bar.setPosition(Vector2f(barXPos, HEIGHT - barHeight));
        }
        
        
        bar.setSize(Vector2f(WIDTH, barWidth)); // Changes the size and starting position to that of a vertical bar
        bar.setPosition(Vector2f(0, barYPos));
        
        for (int i = 0; i < (int) ((barHeight) / (barWidth * 5)) + 1; i++) { // Draws vertical bars, with each bar being spaced 5 bar widths apart
            window.draw(bar);
            barYPos -= barWidth * 5;
            bar.setPosition(Vector2f(0, barYPos));
        }
        
        while (window.pollEvent(event)) { // Checks for events
            if (event.type == Event::KeyPressed) { // IF a key is pressed...
                if (event.key.code == Keyboard::Return) { // Return moves forward
                    return 1;
                }
                if (event.key.code == Keyboard::Escape) { // Pressing escape or the 'X' on top closes the window
                    window.close();
                    return 0;
                }
            }
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }
        }
        
        window.display(); // Displays the window
    }
}

void optionsScreen(RenderWindow& window, const int WIDTH, const int HEIGHT, int& gridWidth, int& gridHeight, Font vtFont) { // Displays the height/width prompt
    Text prompt, quitPrompt, input; // Holds text boxes for width/height prompts and quit prompt, as well as the text input
    bool widthPrompt = true, heightPrompt = false; // Used for switching between the height and width prompt
    string widthInput = "", heightInput = ""; // Used for holding the height/width input for conversion into ints
    Event event; // Holds events
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        prompt.setFont(vtFont); // Sets the attributes of the quit/width/height prompts
        prompt.setCharacterSize(30);
        prompt.setColor(Color::White);
        input.setFont(vtFont);
        input.setCharacterSize(30);
        input.setColor(Color::White);
        quitPrompt.setFont(vtFont);
        quitPrompt.setCharacterSize(30);
        quitPrompt.setColor(Color::White);
        
        
        /* Gets input for width/height */
        if (widthPrompt) { // Displays/Gets width
            prompt.setString("Enter the width of the cell grid:"); // Sets attributes of width prompt
            FloatRect promptRectangle = prompt.getLocalBounds(); // Centers text box
            prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
            prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
            window.draw(prompt); // Draws the prompt
            
            input.setString(widthInput); // Sets attributes of input text box
            FloatRect inputRectangle = input.getLocalBounds(); // Centers the text box
            input.setOrigin(inputRectangle.left + inputRectangle.width / 2.0, inputRectangle.top + inputRectangle.height / 2.0);
            input.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height * 2 + inputRectangle.height));
            window.draw(input); // Draws the input text box
            
            quitPrompt.setString("Press ESC to Quit"); // Sets attributes for the quit prompt
            FloatRect quitPromptRectangle = quitPrompt.getLocalBounds(); // Centers the text box
            quitPrompt.setOrigin(quitPromptRectangle.left + quitPromptRectangle.width / 2.0, quitPromptRectangle.top + quitPromptRectangle.height / 2.0);
            quitPrompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height * 2 + inputRectangle.height * 2 + quitPromptRectangle.height));
            window.draw(quitPrompt); // Draws the quit prompt
            
            while (window.pollEvent(event)) { // Checks for events
                if (event.type == Event::TextEntered) { // If text is entered...
                    if (event.text.unicode > 47 && event.text.unicode < 58) { // And the text is an integer
                        widthInput += static_cast<char> (event.text.unicode); // Adds it to the input
                    }
                    else if (event.text.unicode == 8 && widthInput.length() > 0) { // And the text is a backspace character, removes a letter
                        widthInput.pop_back();
                    }
                }
                if (event.type == Event::KeyPressed) { // IF a key is pressed
                    if (event.key.code == Keyboard::Escape) { // And it's escape, close the window
                        window.close();
                    }
                    if (event.key.code == Keyboard::Return && widthInput != "" && widthInput != "0") { // If its return, and the input is valid, cycles to the height prompt
                        heightPrompt = !heightPrompt;
                        widthPrompt = !widthPrompt;
                    }
                }
            }
        }
        
        else if (heightPrompt) { // Repeats the same process for the height
            prompt.setString("Enter the height of the cell grid:");
            FloatRect promptRectangle = prompt.getLocalBounds();
            prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
            prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
            window.draw(prompt);
            
            input.setString(heightInput);
            FloatRect inputRectangle = input.getLocalBounds();
            input.setOrigin(inputRectangle.left + inputRectangle.width / 2.0, inputRectangle.top + inputRectangle.height / 2.0);
            input.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height * 2 + inputRectangle.height));
            window.draw(input);
            
            quitPrompt.setString("Press ESC to Quit");
            FloatRect quitPromptRectangle = quitPrompt.getLocalBounds();
            quitPrompt.setOrigin(quitPromptRectangle.left + quitPromptRectangle.width / 2.0, quitPromptRectangle.top + quitPromptRectangle.height / 2.0);
            quitPrompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height * 2 + inputRectangle.height * 2 + quitPromptRectangle.height));
            window.draw(quitPrompt);
            
            while (window.pollEvent(event)) {
                if (event.type == Event::TextEntered) {
                    if (event.text.unicode > 47 && event.text.unicode < 58) {
                        heightInput += static_cast<char> (event.text.unicode);
                    }
                    else if (event.text.unicode == 8 && heightInput.length() > 0) {
                        heightInput.pop_back();
                    }
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == Keyboard::Return && heightInput != "" && heightInput != "0") { // Once return is pressed...
                        gridWidth = stoi(widthInput, nullptr, 10); // Converts the width/height input strings to integers, and stores them in the int vars for the width/height
                        gridHeight = stoi(heightInput, nullptr, 10);
                        return;
                    }
                }
            }
        }
        window.display(); // Displays the window
    }
}

void resizeGameBoard(vector< vector<Cell> >& gameBoard, int gridWidth, int gridHeight) { // Resizes the game board to the desired size
    gameBoard.resize(gridHeight); // Resizes the y component of the board
    
    for (int i = 0; i < gameBoard.size(); i++) { // Cycles through each y position, resizing its number of x components to the desired length
        gameBoard.at(i).resize(gridWidth);
    }
    
    for (int i = 0; i < gameBoard.size(); i++) { // Goes through each cell, correctly setting its x and y position
        for (int j = 0; j < gameBoard.at(i).size(); j++) {
            gameBoard.at(i).at(j).setXPos(i);
            gameBoard.at(i).at(j).setYPos(j);
        }
    }
}

void displayGameBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight) { // Displays the game board grid and any active cells
    RectangleShape bar, litCell, activeCell; // Creates shapes for the board
    
    double barWidth, barHeight, barXPos, barYPos; // Stores attributes of the grid bars 
    barHeight = (HEIGHT * 0.9) / (gridHeight * 5.0); // Sets the attributes of the bars
    barWidth = WIDTH / (gridWidth * 5.0);
    barXPos = 0;
    barYPos = HEIGHT - barHeight;
    bar.setSize(Vector2f(WIDTH, barHeight));
    bar.setFillColor(Color(54, 54, 56));
    
    double cellWidth = barWidth * 4, cellHeight = barHeight * 4, cellSelectorXPos, cellSelectorYPos; // Sets the attributes for the cells
    activeCell.setFillColor(Color::Yellow);
    activeCell.setSize(Vector2f(cellWidth, cellHeight));
    
    /* Drawing grid... */
    for (int i = 0; i < gridHeight + 1; i++) { // Draws vertical bars 5 bar widths apart
        bar.setPosition(Vector2f(0, barYPos));
        window.draw(bar);
        barYPos -= barHeight * 5;
    }
    bar.setSize(Vector2f(barWidth, HEIGHT * 0.9)); // Draws horizontal bars 5 bar widths apart
    for (int i = 0; i < gridWidth + 1; i++) {
        bar.setPosition(Vector2f(barXPos, HEIGHT * 0.1));
        window.draw(bar);
        barXPos += barWidth * 5;
    }
        
    /* Drawing the active cells... */
    for (int i = 0; i < gridWidth; i++) { // Checks each cell to see if it's alive or not, and draws it in the correct position if it is
        for (int j = 0; j < gridHeight; j++) {
            if (gameBoard.at(j).at(i).getState() == true) {
                cellSelectorXPos = barWidth + (barWidth * 5 * i);
                cellSelectorYPos = barYPos + (barHeight * 6) + (barHeight * 5 * j);
                activeCell.setPosition(Vector2f(cellSelectorXPos, cellSelectorYPos));
                window.draw(activeCell);
            }
        }
    }
} 

void advanceGeneration(vector< vector<Cell> >& gameBoard) { // Advances the cell generation, according to a set of rules
    int numNeighbors; // Stores the number of neighbors of each cell
     
    for (int i = 0; i < gameBoard.size(); i++) { // Goes through each cell and counts it's neighors (left/right, up/down, diagonally), setting its new neighbor count
        for (int j = 0; j < gameBoard.at(i).size(); j++) {
            numNeighbors = 0;
            
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    try { // Catches out of bound errors when checking border cells
                        if (gameBoard.at(i + x).at(j + y).getState() && (x != 0 || y != 0)) {
                            numNeighbors++;
                        }
                    }
                    catch (const out_of_range& oor) {
                    }
                }
            }
            gameBoard.at(i).at(j).setNumNeighbors(numNeighbors);
        }
    }
    for (int i = 0; i < gameBoard.size(); i++) { // Goes through each cell, and switches it on or off depending on its state and number of neighbors
        for (int j = 0; j < gameBoard.at(i).size(); j++) {
            numNeighbors = gameBoard.at(i).at(j).getNumNeighbors();
            
            // Da Rules: Dies if num neighbors > 3 or < 2, and comes back alive if it's dead and has exactly 3 neighbors
            if (numNeighbors < 2) { 
                gameBoard.at(i).at(j).setState(false);
            }
            else if (numNeighbors > 3) {
                gameBoard.at(i).at(j).setState(false);
            }
            else if (numNeighbors == 3 && !gameBoard.at(i).at(j).getState()) {
                gameBoard.at(i).at(j).setState(true);
            }
        }
    }
            
}
void pickBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, Font vtFont) { // Displays the options for pickking a predefined board of cells
    Text prompt; // Holds the text for the prompts
    Event event; // Holds events
    
    resizeGameBoard(gameBoard, 50, 50); // Resizes the game board to a default 50, 50 size
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        prompt.setFont(vtFont); // Sets the attributes of the prompt
        prompt.setCharacterSize(20);
        prompt.setColor(Color::White);
        prompt.setString("Select the pre-defined board you want to use:\n1. R-Pentomino\n2. Acorn\n3. Pulsar\n4. Caterer\n5. Multum In Parvo"); // Lists the options for the predefined boards
        FloatRect promptRectangle = prompt.getLocalBounds(); // Centers the prompt
        prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
        prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
        window.draw(prompt); // Draws the prompt
        
        while (window.pollEvent(event)) { // Checks for events
            if (event.type == Event::KeyPressed) { // Checks for key presses
                if (event.key.code == Keyboard::Num1) { // 1. Draws an R-pentomino
                    gameBoard.at(25).at(25).setState(true);
                    gameBoard.at(24).at(25).setState(true);
                    gameBoard.at(24).at(26).setState(true);
                    gameBoard.at(25).at(24).setState(true);
                    gameBoard.at(26).at(25).setState(true);
                    return;
                }
                if (event.key.code == Keyboard::Num2) { // 2. Draws an acorn
                    gameBoard.at(25).at(25).setState(true);
                    gameBoard.at(26).at(26).setState(true);
                    gameBoard.at(26).at(27).setState(true);
                    gameBoard.at(26).at(28).setState(true);
                    gameBoard.at(24).at(23).setState(true);
                    gameBoard.at(26).at(23).setState(true);
                    gameBoard.at(26).at(22).setState(true);
                    return;
                }
                if (event.key.code == Keyboard::Num3) { // 3. Draws a pulsar
                    for (int i = 2; i < 5; i++) {
                        gameBoard.at(25 - i).at(26).setState(true);
                        gameBoard.at(25 - i).at(31).setState(true);
                        gameBoard.at(24).at(25 + i).setState(true);
                        gameBoard.at(19).at(25 + i).setState(true);
                        
                        gameBoard.at(25 + i).at(26).setState(true);
                        gameBoard.at(25 + i).at(31).setState(true);
                        gameBoard.at(26).at(25 + i).setState(true);
                        gameBoard.at(31).at(25 + i).setState(true);
                        
                        gameBoard.at(25 - i).at(24).setState(true);
                        gameBoard.at(25 - i).at(19).setState(true);
                        gameBoard.at(24).at(25 - i).setState(true);
                        gameBoard.at(19).at(25 - i).setState(true);
                        
                        gameBoard.at(25 + i).at(24).setState(true);
                        gameBoard.at(25 + i).at(19).setState(true);
                        gameBoard.at(26).at(25 - i).setState(true);
                        gameBoard.at(31).at(25 - i).setState(true);
                    }
                    return;
                }
                if (event.key.code == Keyboard::Num4) { // 4. Draws a caterer
                    gameBoard.at(25).at(25).setState(true);
                    gameBoard.at(24).at(25).setState(true);
                    gameBoard.at(24).at(26).setState(true);
                    gameBoard.at(24).at(27).setState(true);
                    gameBoard.at(24).at(28).setState(true);
                    gameBoard.at(27).at(24).setState(true);
                    gameBoard.at(28).at(23).setState(true);
                    gameBoard.at(28).at(22).setState(true);
                    gameBoard.at(26).at(21).setState(true);
                    gameBoard.at(25).at(21).setState(true);
                    gameBoard.at(24).at(21).setState(true);
                    gameBoard.at(23).at(23).setState(true);
                    return;
                }
                if (event.key.code == Keyboard::Num5) { // 5. Draws a Multum in Parvo
                    gameBoard.at(25).at(25).setState(true);
                    gameBoard.at(26).at(24).setState(true);
                    gameBoard.at(27).at(23).setState(true);
                    gameBoard.at(24).at(26).setState(true);
                    gameBoard.at(24).at(27).setState(true);
                    gameBoard.at(24).at(28).setState(true);
                    gameBoard.at(25).at(28).setState(true);
                    return;
                }
            }
        }
        
        window.display(); // Displays the window
    }
    
}

void manuallySetBoard(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont) { // Displays a grid for manually activating cells
    Text prompt; // Holds the text prompt
    RectangleShape cellSelector; // Holds the shape for the cell activator
    
    Event event; // Holds events
    
    int xPos = 0, yPos = 0; // Holds the 'ideal' position of the cell selector
    double barWidth, barHeight, barXPos, barYPos; // Holds the attributes of the bar, used for positoning the cell selector
    barHeight = (HEIGHT * 0.9) / (gridHeight * 5.0);
    barWidth = WIDTH / (gridWidth * 5.0);
    barXPos = 0;
    barYPos = HEIGHT - barHeight;
    
    double cellWidth = barWidth * 4, cellHeight = barHeight * 4, cellSelectorXPos, cellSelectorYPos; // Sets the attributes of the cell selector
    cellSelector.setFillColor(Color::Blue);
    cellSelector.setSize(Vector2f(cellWidth, cellHeight));
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        /* Drawing grid... */
        displayGameBoard(window, gameBoard, WIDTH, HEIGHT, gridWidth, gridHeight); // Displays the game board as it currently is
        
        /* Drawing cell... */
        cellSelectorXPos = barWidth + (barWidth * 5 * xPos); // Sets the attributes of the cell selector
        cellSelectorYPos = barYPos - (barHeight * 5 * (gridHeight + 1)) + (barHeight * 6) + (barHeight * 5 * yPos);
        cellSelector.setPosition(Vector2f(cellSelectorXPos, cellSelectorYPos));
        window.draw(cellSelector); // Draws the cell selector
        
        /* Drawing prompt... */
        prompt.setFont(vtFont); // Sets the attributes of the prompt
        prompt.setCharacterSize(15);
        prompt.setColor(Color::White);
        prompt.setString("Mark active cells in the grid below using the spacebar\nPress ENTER when finished");
        FloatRect promptRectangle = prompt.getLocalBounds(); // Centers the prompt
        prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
        prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
        window.draw(prompt); // Draws the prompt
        
        
        while (window.pollEvent(event)) { // Checks for events
            if (event.type == Event::KeyPressed) { // Checks for key presses
                if (event.key.code == Keyboard::Escape) { // Pressing escape closes the window
                    window.close();
                }
                if (event.key.code == Keyboard::Return) { // Pressing return continues the program
                    return;
                }
                if (event.key.code == Keyboard::Left && xPos > 0) { // Arrow keys moves the selector around, bounded by the borders
                    xPos--;
                }
                if (event.key.code == Keyboard::Right && xPos < gridWidth - 1) {
                    xPos++;
                }
                if (event.key.code == Keyboard::Up && yPos > 0) {
                    yPos--;
                }
                if (event.key.code == Keyboard::Down && yPos < gridHeight - 1) {
                    yPos++;
                }
                if (event.key.code == Keyboard::Space) { // Pressing spaces switches the current cell on/off
                    gameBoard.at(yPos).at(xPos).setState(!gameBoard.at(yPos).at(xPos).getState());
                }
            }
        }
        
        window.display(); /// Displays the window
    }
}

bool setGameBoardCells(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont) { // Displays the prompt for wither manually setting cells or picking a predefined board
    Text prompt; // Holds the text prompt
    Event event; // Holds events
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        prompt.setFont(vtFont); // Sets the attributes of the prompt
        prompt.setCharacterSize(30);
        prompt.setColor(Color::White);
        
        prompt.setString("Do you want to:\n1. Set cells manually\n2. Select a pattern of cells");
        FloatRect promptRectangle = prompt.getLocalBounds(); // Centers the prompt
        prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
        prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
        window.draw(prompt); // Draws the prompt
        
        while (window.pollEvent(event)) { // Checks for events
            if (event.type == Event::KeyPressed) { // If a key is pressed
                if (event.key.code == Keyboard::Num1) { // Pressing 1 signals that the user wants to manually set the board
                    return true;
                }
                else if (event.key.code == Keyboard::Num2) { // Pressing 2 signlas that the user wants to select a board
                    return false;
                }
                else if (event.key.code == Keyboard::Escape) { // Pressing the escape key closes the window
                    window.close();
                    return false;
                }
            }
        }
        
        window.display(); // Displays the window
    }
}

void playGame(RenderWindow& window, vector< vector<Cell> >& gameBoard, const int WIDTH, const int HEIGHT, int gridWidth, int gridHeight, Font vtFont) { // Displays the game board as generations advance
    Text prompt; // Holds the text prompt
    Event event; // Holds events
    int generationNum = 0; // Holds the current number of generations elapsed
    
    while (window.isOpen()) {
        window.clear(); // Clears the window
        
        /* Displaying grid */
        displayGameBoard(window, gameBoard, WIDTH, HEIGHT, gridWidth, gridHeight); // Displays the game board
        
        /* Displaying prompt */
        prompt.setFont(vtFont); // Sets the attributes of the prompt
        prompt.setCharacterSize(15);
        prompt.setColor(Color::White);
        prompt.setString("GENERATION " + to_string(generationNum) + "\nUse the RIGHT arrow key to advance in generation. Press ENTER when finished."); // Shows the prompt and the generation number
        FloatRect promptRectangle = prompt.getLocalBounds(); // Centers the prompt
        prompt.setOrigin(promptRectangle.left + promptRectangle.width / 2.0, promptRectangle.top + promptRectangle.height / 2.0);
        prompt.setPosition(Vector2f(WIDTH / 2.0, promptRectangle.height));
        window.draw(prompt); // Draws the prompt
        
        while (window.pollEvent(event)) { // Checks for events
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) { // Escape key closes the window
                    window.close();
                }
                if (event.key.code == Keyboard::Return) { // Return continues the program
                    return;
                }
                if (event.key.code == Keyboard::Right) { // Right key advances the generation
                    advanceGeneration(gameBoard);
                    generationNum++;
                }
            }
        }
        
        window.display(); // Displays the window
    }
}