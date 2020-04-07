#ifndef MAZE_INTERFACE_H
#define MAZE_INTERFACE_H

class MazeInterface
{
private:
	int height, width, layer;
	int*** cube;
	int*** solvedCube;
	bool solvable = true;
	virtual bool find_path(int HEIGHT, int WIDTH, int LAYER) = 0;
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY, L, R, U, D, O, I };

public:
	MazeInterface(void) {}
	~MazeInterface(void) {}

	virtual void setValue(char** input) = 0;
	virtual bool find_maze_path() = 0;
	virtual void freeSpace() = 0;
	virtual void setSolvable(bool input) = 0;
	virtual std::string toString() const = 0;
};
#endif 