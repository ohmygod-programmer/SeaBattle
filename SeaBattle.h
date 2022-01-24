#include <string>
#define SIZE_OF_FIELD 10

class Cell;

class Ship {
private:
	int size;
	Cell* cells[4];
	int health;
public: 
	Ship(int num = 0);
	void setsize(int size);
	void setcells(Cell* first, Cell* seconds = nullptr, Cell* third = nullptr, Cell* fourth = nullptr);
	int shoot();
	int gethealth();
};

class Cell
{
private:
	char status;
	Ship* sh; //—сылка на корабль
public:
	Cell();
	int shoot();
	void setship(Ship* ship);
	char getstatus();
	Ship* getship();
};

class Gamer
{
protected:
	Ship ships[10];
	void clearall();
public:
	Cell field[SIZE_OF_FIELD][SIZE_OF_FIELD];
	std::string name;
	int shoot(int x, int y);
	virtual void initialize() {};
	virtual int Turn(Gamer* Enemy) { return -1; };
	int getcountofships();
	void dodeadoreol(Ship* ship);
	
	
};
class ConsoleGamer : public Gamer
{
public:
	void initialize();
	virtual int Turn(Gamer* Enemy);
};

class RandomGamer : public Gamer
{
public:
	void initialize();
	virtual int Turn(Gamer* Enemy);
};

class OptimalGamer : public Gamer
{
private:
	int lastx;
	int lasty;
	bool lasthit;
public:
	int Turn(Gamer* Enemy);
};

void consolewritefields(Gamer Owner, Gamer Enemy);
void consolewritefield(Gamer Owner);