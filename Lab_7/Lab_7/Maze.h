#ifndef MAZE_H
#define MAZE_H
#include <fstream>
#include <sstream>
#include "MazeInterface.h"

using namespace std;

class Maze : public MazeInterface
{
private:
	int height, width, layer;
	int*** cube;
	int*** solvedCube;
	bool solvable = true;
	bool find_path(int HEIGHT, int WIDTH, int LAYER);
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY, L, R, U, D, O, I };
	//               0     1        2     3     4          5  6  7  8  9  10
public:
	Maze(void) {}
	~Maze(void) { freeSpace(); }

	virtual void setValue(char** input);
	virtual bool find_maze_path() { return find_path(0, 0, 0); }
	void freeSpace();
	void setSolvable(bool input);
	virtual std::string toString() const;
};
#endif 