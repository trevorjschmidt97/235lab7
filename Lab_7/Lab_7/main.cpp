#include <fstream>
#include "Maze.h"

int main(int argc, char* argv[])
{
	ofstream out(argv[2]);
	Maze maze; 

	maze.setValue(argv); //Creates and fills maze using the input file
	if (!maze.find_maze_path()) { maze.setSolvable(false); } //Solves maze
	out << maze.toString(); //Outs maze and solution
	
	return 0;
}