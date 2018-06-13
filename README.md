![text](https://github.com/AdamBeziou/Conway/blob/master/Docs/Conway.gif "Game Demo")

# Conway
An implementation of Conway's Game of Life in C++ and SFML.
Created as part of my final project in CSCI 261, Programming Concepts,
at the Colorado School of Mines.

## Prerequisites
* [SFML](https://www.sfml-dev.org)
* C++

## Build Instructions
1. Clone the repository
> $ git clone https://github.com/AdamBeziou/Conway.git

2. [Download SFML](https://www.sfml-dev.org/download/sfml/2.5.0/) and follow the [instructions on their website](https://www.sfml-dev.org/tutorials/2.5/#getting-started) for setting up SFML and running the application.

3. If you are on Windows and don't wish to use either Code::Blocks or Visual Studio, follow these instructions:
    * Download the "GCC 7.3.0 MinGW" flavor of SFML from [here](https://www.sfml-dev.org/download/sfml/2.5.0/) for your 32-bit or 64-bit OS.
    * If you don't want to compile SFML from source, download and install the correct MinGW version from [the download page](https://www.sfml-dev.org/download/sfml/2.5.0/) and unzip the file to a directory of your choosing.
    * If you want to compile SFML from source, follow [these instructions](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php).
    * Open up your favorite command prompt and navigate to the "Data" directory where you cloned the Git repository.
    * Compile the Cell.cpp, GameFunctions.cpp, and main.cpp files using GCC:
    * > $ g++ -c Cell.cpp GameFunctions.cpp main.cpp -I\<your SFML directory here\>\include
    * Link the Cell.o, GameFunctions.o, main.o, and required SFML files to produce the output file:
    * > $ g++ Cell.o GameFunctions.o main.o -L\<your SFML directory here\>\lib -lsfml-graphics -lsfml-window -lsfml-system
    * If the output file will not start because some ".dll" files are missing, copy the contents of the "bin" folder in your SFML directory to the directory where the output file is located.

