#include "Maze.h"

// FUNCITON TO CREATE AND FILL A NORMAL, AND A TEMP MAZE TO BE SOLVED
void Maze::setValue(char** input)
{
	ifstream in(input[1]); // SETS IN STREAM FROM INPUT FILE
	in >> this->height >> this->width >> this->layer;

	// CREATES CUBES 
	this->cube = new int**[height];
	this->solvedCube = new int**[height];
	for (int i = 0; i < height; i++)
	{
		cube[i] = new int*[width];
		solvedCube[i] = new int*[width];

		for (int j = 0; j < width; j++)
		{
			cube[i][j] = new int[layer];
			solvedCube[i][j] = new int[layer];
		}
	}

	//FILLS CUBES FROM INPUT FILE
	for (int i = 0; i < layer; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				in >> cube[j][k][i];
				solvedCube[j][k][i] = cube[j][k][i];
			}
		}
	}
}

 

// FUNCTION TO FIND PATH OF MAZE, OR DETERMINE IF UNSOLVABLE
bool Maze::find_path(int HEIGHT, int WIDTH, int LAYER)
{    
	//BASE CASES
	if ((HEIGHT < 0) || (HEIGHT >= this->height) || (WIDTH < 0) ||
		(WIDTH >= this->width) || (LAYER < 0) || (LAYER >= this->layer))
	{
		return false; // IF OUT OF BOUNDS, RETURNS FALSE                          
	}																	
																			 
	if (solvedCube[HEIGHT][WIDTH][LAYER] != OPEN)							
	{																	
		return false; // IF NOT AN OPEN PATH, RETURNS FALSE					  
	}																		 
						
	if ((HEIGHT == this->height - 1) &&
		(WIDTH == this->width - 1) &&
		(LAYER == this->layer - 1))
	{
		solvedCube[HEIGHT][WIDTH][LAYER] = EXIT;
		return true; // IF IS END CORNER, PATH IS SUCCESSFULL AND EXITS FUNCTION          
	}
	// END BASE CASES

	solvedCube[HEIGHT][WIDTH][LAYER] = PATH; // ASSUME PATH	

	if (find_path(HEIGHT, WIDTH - 1, LAYER))
	{  // CHECK LEFT
		solvedCube[HEIGHT][WIDTH][LAYER] = L;
		return true;
	}
	else if (find_path(HEIGHT, WIDTH + 1, LAYER))
	{  // CHECK RIGHT
		solvedCube[HEIGHT][WIDTH][LAYER] = R;
		return true;
	}
	else if (find_path(HEIGHT - 1, WIDTH, LAYER))
	{  // CHECK UP
		solvedCube[HEIGHT][WIDTH][LAYER] = U;
		return true;
	}
	else if (find_path(HEIGHT + 1, WIDTH, LAYER))
	{  // CHECK DOWN
		solvedCube[HEIGHT][WIDTH][LAYER] = D;
		return true;
	}
	else if (find_path(HEIGHT, WIDTH, LAYER - 1))
	{  // CHECK OUT
		solvedCube[HEIGHT][WIDTH][LAYER] = O;
		return true;
	}
	else if (find_path(HEIGHT, WIDTH, LAYER + 1))
	{  // CHECK IN
		solvedCube[HEIGHT][WIDTH][LAYER] = I;
		return true;
	}

	// NOT A VIABLE PATH, ASSIGN AS TEMPORARY
	solvedCube[HEIGHT][WIDTH][LAYER] = TEMPORARY; 
	return false;
}



// FUNCTION TO FREE SPACE, CALLED ON BY CLASS DESTRUCTOR
void Maze::freeSpace()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			delete[] cube[i][j];
			delete[] solvedCube[i][j];
		}
		delete[] cube[i];
		delete[] solvedCube[i];
	}
	delete[] cube;
	delete[] solvedCube;
}



// FUNCTION TO ALLOW MAIN TO CALL IF A MAZE IS SOLVABLE
void Maze::setSolvable(bool input)
{ //WILL BE USED IN TOSTRING TO CHANGE OUTPUT
	solvable = input;
}



string Maze::toString() const
{
	stringstream ss; //USES STRINGSREAM 

	// STREAMS THE INPUT MAZE
	ss << "Solve Maze: " << endl;
	for (int i = 0; i < layer; i++)
	{
		ss << "Layer " << i + 1 << endl;
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				if (cube[j][k][i] == 0) { ss << "_ "; }
				else { ss << "X "; }
			}
			ss << endl;
		}
	}

	// IF UNSOLVABLE, RETURNS STRING HERE
	if (!solvable)
	{
		ss << endl << "No Solution Exists!";
		return ss.str();
	}

	// ELSE, STREAMS THE SOLUTION MAZE
	ss << endl << "Solution: " << endl;
	for (int i = 0; i < layer; i++)
	{
		ss << "Layer " << i + 1 << endl;
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				if (j == height - 1 && k == width - 1 && i == layer - 1) { ss << "E "; }
				else if (solvedCube[j][k][i] == L) { ss << "L "; }
				else if (solvedCube[j][k][i] == R) { ss << "R "; }
				else if (solvedCube[j][k][i] == U) { ss << "U "; }
				else if (solvedCube[j][k][i] == D) { ss << "D "; }
				else if (solvedCube[j][k][i] == O) { ss << "O "; }
				else if (solvedCube[j][k][i] == I) { ss << "I "; }
				else if (solvedCube[j][k][i] == OPEN || 
					     solvedCube[j][k][i] == TEMPORARY) { ss << "_ "; }
				else if (solvedCube[j][k][i] == BLOCKED) { ss << "X "; }		
			}
			ss << endl;
		}
	}
	return ss.str();
}