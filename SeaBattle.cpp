#include "SeaBattle.h"
#include <iostream>

#define MAX(a, b) (a<b)?b:a;
#define MIN(a, b) (a>b)?b:a;
using namespace std;

Ship::Ship(int num) : size(num), health(num) {
	cells[0] = nullptr;
	cells[1] = nullptr;
	cells[2] = nullptr;
	cells[3] = nullptr;
}

void Ship::setsize(int num) {
	size = num;
	health = num;
}

void Ship::setcells(Cell* first, Cell* second, Cell* third, Cell* fourth) {
	cells[0] = first;
	cells[1] = second;
	cells[2] = third;
	cells[3] = fourth;
}

int Ship::shoot() { // 0 - Alive, 1 - Dead
	health -= 1;
	if (health == 0) {
		return 1;
	}
	return 0;
}

int Ship::gethealth() {
	return health;
}

Cell::Cell() : status(0), sh(nullptr) {
}

int Cell::shoot() {
	if (status == 1) {
		return -1;
	}
	status = 1;
	if (sh != nullptr) {
		if (sh->shoot()) {
			return 1;
		}
	}
	return 0;
}


void Cell::setship(Ship* ship) {
	sh = ship;
}

Ship* Cell::getship() {
	return sh;
}

char Cell::getstatus() {
	return status;
}

int Gamer::shoot(int x, int y) { //0 - OK, Non ships; 1 - OK, Bang ship; 2 - OK, Dead ship; 3 - Already shooted
	return field[x][y].shoot();
}

int Gamer::getcountofships() {
	int k = 0;
	for (int i = 0; i < 10; i++) {
		if (ships[i].gethealth() != 0) {
			k++;
		}
	}
	return k;
}

void Gamer::dodeadoreol(Ship* ship) {
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		for (int j = 0; j < SIZE_OF_FIELD; j++){
			if (field[i][j].getship() == ship) {
				if (i + 1 < SIZE_OF_FIELD) {
					field[i + 1][j].shoot();
				}
				if (j + 1 < SIZE_OF_FIELD) {
					field[i][j + 1].shoot();
				}
				if (i - 1 >= 0) {
					field[i - 1][j].shoot();
				}
				if (j - 1 >= 0) {
					field[i][j - 1].shoot();
				}
				if (i + 1 < SIZE_OF_FIELD && j + 1 < SIZE_OF_FIELD) {
					field[i + 1][j + 1].shoot();
				}
				if (i + 1 < SIZE_OF_FIELD && j - 1 >= 0) {
					field[i + 1][j - 1].shoot();
				}
				if (i - 1 >= 0 && j + 1 < SIZE_OF_FIELD) {
					field[i - 1][j + 1].shoot();
				}
				if (i - 1 >= 0 && j - 1 >= 0) {
					field[i - 1][j - 1].shoot();
				}
				
				
				
				
				
		}
}
	}
}

void Gamer::clearall() {
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		for (int j = 0; j < SIZE_OF_FIELD; j++) {
			field[i][j] = Cell();
		}
		ships[i] = Ship();
	}
}

int proverka(int num, int** cord) {
	bool s1_is_equal = 1;
	bool s2_is_equal = 1;
	bool s1_is_not_equal = 1;
	bool s2_is_not_equal = 1;
	for (int i = 0; i < num - 1; i++) {
		if (cord[0][i] != cord[0][i + 1]) {
			s1_is_equal = 0;
		}
		if (cord[1][i] != cord[1][i + 1]) {
			s2_is_equal = 0;
		}
		if (cord[0][i] == cord[0][i + 1]) {
			s1_is_not_equal = 0;
		}
		if (cord[1][i] == cord[1][i + 1]) {
			s2_is_not_equal = 0;
		}
	}
	if (s1_is_equal && s2_is_not_equal) {
		int max = cord[1][0];
		int min = cord[1][0];
		for (int i = 1; i < num; i++) {
			max = MAX(max, cord[1][i]);
			min = MIN(min, cord[1][i]);
		}
		if (max - min != num - 1) {
			return 1;
		}
		return 0;
	}
	else
		if (s1_is_not_equal && s2_is_equal) {
			int max = cord[0][0];
			int min = cord[0][0];
			for (int i = 1; i < num; i++) {
				max = MAX(max, cord[0][i]);
				min = MIN(min, cord[0][i]);
			}
			if (max - min != num - 1) {
				return 1;
			}
			return 0;
		}
		else {
			return 1;
		}
}

void consolescancells(string name, int size, int* cord[2]) {
	cord[0] = new(int[size]);
	cord[1] = new(int[size]);
	string number;
	switch (size)
	{
	case 1:
		number = "one";
	case 2:
		number = "two";
	case 3:
		number = "three";
	case 4:
		number = "four";
	}
	cout << "Shoose " << number << " cells to " << name << " : \n";

	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". ";
		char c;
		cin >> c >> cord[1][i];
		cord[0][i] = c - 'A';
		cord[1][i] -= 1;
	}
	


	while (proverka(size, cord)) {
		cout << "Uncorrect\n";
		for (int i = 0; i < size; i++) {
			cout << i + 1 << ". ";
			char c;
			cin >> c >> cord[1][i];
			cord[0][i] = c - 'A';
			cord[1][i] -= 1;
		}
	}
}



void ConsoleGamer::initialize() {
	this->clearall();
	int* cord[2];

	bool flag = 1;
	while (flag) {
		flag = 0;
		consolescancells("battleship", 4, cord);
		for (int i = 0; i < 3; i++) {
			if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			cout << "Incorrect\n";
		}
	}
	ships[0].setsize(4);
	ships[0].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]], &field[cord[0][3]][cord[1][3]]);
	for (int j = 0; j < 4; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[0]);
	}
	consolewritefield(*this);

	flag = 1;
	while (flag) {
		flag = 0;
		consolescancells("cruiser", 3, cord);
		for (int i = 0; i < 3; i++) {
			if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			cout << "Incorrect\n";
		}
	}
	ships[1].setsize(3);
	ships[1].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]]);
	for (int j = 0; j < 3; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[1]);
	}
	consolewritefield(*this);

	flag = 1;
	while (flag) {
		flag = 0;
		consolescancells("cruiser", 3, cord);
		for (int i = 0; i < 3; i++) {
			if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			cout << "Incorrect\n";
		}
	}
	ships[2].setsize(3);
	ships[2].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]], &field[cord[0][3]][cord[1][3]]);
	for (int j = 0; j < 3; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[1]);
	}
	consolewritefield(*this);

	for (int i = 3; i < 6; i++) {
		flag = 1;
		while (flag) {
			flag = 0;
			consolescancells("destroyer", 2, cord);
			for (int i = 0; i < 2; i++) {
				if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				cout << "Incorrect\n";
			}
		}
		ships[i].setsize(2);
		ships[i].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]]);
		field[cord[0][0]][cord[1][0]].setship(&ships[i]);
		field[cord[0][1]][cord[1][1]].setship(&ships[i]);
		consolewritefield(*this);
	}

	for (int i = 6; i < 10; i++) {
		flag = 1;
		while (flag) {
			flag = 0;
			consolescancells("torpedo boat", 1, cord);
			for (int i = 0; i < 1; i++) {
				if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				cout << "Incorrect\n";
			}
		}
		ships[i].setsize(1);
		ships[i].setcells(&field[cord[0][0]][cord[1][0]]);
		field[cord[0][0]][cord[1][0]].setship(&ships[i]);
		consolewritefield(*this);
	};
}

int ConsoleGamer::Turn(Gamer* Enemy) {
	int flag = 1;
	while (1) {
		char x;
		int y;
		cout << "Shoose cell to shoot\n";
		cin >> x >> y;
		x -= 'A';
		y -= 1;
		if (Enemy->field[x][y].getstatus() == 0) {
			if (Enemy->field[x][y].shoot() == 1) {
				Enemy->dodeadoreol(Enemy->field[x][y].getship());
				return 2;
			}
			if (Enemy->field[x][y].getship() == nullptr) {
				return 0;
			}
			else return 1;
		}
	}
}


void randomscancells(int size, int* cord[2]) {
	int flag = 1;
	cord[0] = new(int[size]);
	cord[1] = new(int[size]);
	cord[0][0] = rand() % SIZE_OF_FIELD;
	cord[1][0] = rand() % SIZE_OF_FIELD;
	if (size == 1) {
		flag = 0;
	}
	while (flag) {
		flag = 0;
		int ran = rand() % 4;
		if (ran < 2) {
			if (ran == 0) {
				for (int i = 1; i < size; i++) {
					cord[0][i] = cord[0][0] + i;
					cord[1][i] = cord[1][0];
				}
			}
			else {
				for (int i = 1; i < size; i++) {
					cord[0][i] = cord[0][0] - i;
					cord[1][i] = cord[1][0];
				}
			}
		}
		else {
			if (ran == 2) {
				for (int i = 1; i < size; i++) {
					cord[1][i] = cord[1][0] + i;
					cord[0][i] = cord[0][0];
				}
			}
			else {
				for (int i = 1; i < size; i++) {
					cord[1][i] = cord[1][0] - i;
					cord[0][i] = cord[0][0];
				}
			}
		}
		if (cord[0][size-1] < 0 || cord[0][size-1] > 9) {
			flag = 1;
		}
		if (cord[1][size-1] < 0 || cord[1][size-1] > 9) {
			flag = 1;
		}

	}

}

void RandomGamer::initialize() {
	this->clearall();

	int* cord[2];
	cout << "Generating field to RandomGamer...\n";
	randomscancells(4, cord);
	ships[0].setsize(4);
	ships[0].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]], &field[cord[0][3]][cord[1][3]]);
	for (int j = 0; j < 4; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[0]);
	}

	cout << "10% complete...\n";

	bool flag = 1;
	while (flag) {
		flag = 0;
		randomscancells(3, cord);
		for (int i = 0; i < 3; i++) {
			if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i]+1<SIZE_OF_FIELD && field[cord[0][i]+1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i]+1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
		}
	}
	ships[1].setsize(3);
	ships[1].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]]);
	for (int j = 0; j < 3; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[1]);
	}

	flag = 1;
	while (flag) {
		flag = 0;
		randomscancells(3, cord);
		for (int i = 0; i < 3; i++) {
			if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
				flag = 1;
				break;
			}
			if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
				flag = 1;
				break;
			}
		}
	}
	ships[2].setsize(3);
	ships[2].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]],
		&field[cord[0][2]][cord[1][2]], &field[cord[0][3]][cord[1][3]]);
	for (int j = 0; j < 3; j++) {
		field[cord[0][j]][cord[1][j]].setship(&ships[2]);
	}

	cout << "30% complete...\n";

	for (int i = 3; i < 6; i++) {
		flag = 1;
		while (flag) {
			flag = 0;
			randomscancells(2, cord);
			for (int i = 0; i < 2; i++) {
				if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
			}
		}
		ships[i].setsize(2);
		ships[i].setcells(&field[cord[0][0]][cord[1][0]], &field[cord[0][1]][cord[1][1]]);
		field[cord[0][0]][cord[1][0]].setship(&ships[i]);
		field[cord[0][1]][cord[1][1]].setship(&ships[i]);
	}


	cout << "60% complete...\n";

	for (int i = 6; i < 10; i++) {
		flag = 1;
		while (flag) {
			flag = 0;
			randomscancells(1, cord);
			for (int i = 0; i < 1; i++) {
				if (field[cord[0][i]][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i]][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i]].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[1][i] - 1 >= 0 && field[cord[0][i]][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] + 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] + 1 < SIZE_OF_FIELD && cord[1][i] - 1 >= 0 && field[cord[0][i] + 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] + 1 < SIZE_OF_FIELD && field[cord[0][i] - 1][cord[1][i] + 1].getship() != nullptr) {
					flag = 1;
					break;
				}
				if (cord[0][i] - 1 >= 0 && cord[1][i] - 1 >= 0 && field[cord[0][i] - 1][cord[1][i] - 1].getship() != nullptr) {
					flag = 1;
					break;
				}
			}
		}
		ships[i].setsize(1);
		ships[i].setcells(&field[cord[0][0]][cord[1][0]]);
		field[cord[0][0]][cord[1][0]].setship(&ships[i]);
	};

	cout << "100% complete.  \n";
}


int RandomGamer::Turn(Gamer* Enemy) {
	int flag = 1;
	while (1) {
		int x = rand() % SIZE_OF_FIELD;
		int y = rand() % SIZE_OF_FIELD;
		if (Enemy->field[x][y].getstatus() == 0) {
			if (Enemy->field[x][y].shoot() == 1) {
				Enemy->dodeadoreol(Enemy->field[x][y].getship());
				return 2;
			}
			if (Enemy->field[x][y].getship() == nullptr) {
				return 0;
			}
			else return 1;
		}
	}
}


int OptimalGamer::Turn(Gamer* Enemy) {
	int flag = 1;
	while (1) {
		int x = rand() % SIZE_OF_FIELD;
		int y = rand() % SIZE_OF_FIELD;
		if (Enemy->field[x][y].getstatus() == 0) {
			if (Enemy->field[x][y].shoot() == 1) {
				Enemy->dodeadoreol(Enemy->field[x][y].getship());
				return 2;
			}
			if (Enemy->field[x][y].getship() == nullptr) {
				return 0;
			}
			else return 1;
		}
	}
}

void consolewritesymbol(char c, int num) {
	for (int i = 0; i < num; i++) {
		cout << c;
	}
}

void consolewritefield(Gamer Owner) {
	for (int i = 0; i < 20; i++) {
		cout << "*";
	}
	cout << "\n";
	
	consolewritesymbol(' ', 2);
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		consolewritesymbol(' ', 1);
		consolewritesymbol('A' + i, 1);
	}
	consolewritesymbol(' ', 1);
	consolewritesymbol('\n', 1);

	consolewritesymbol(' ', 2);
	consolewritesymbol('_', 21);
	consolewritesymbol('\n', 1);

	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		if (i < 9) {
			consolewritesymbol('1' + i, 1);
			consolewritesymbol(' ', 1);
		}
		else {
			consolewritesymbol('1', 1);
			consolewritesymbol('0'+ i - 9, 1);
		}
		for (int j = 0; j < SIZE_OF_FIELD; j++) {
			consolewritesymbol('|', 1);
			if (Owner.field[j][i].getship() == nullptr) {
				if (Owner.field[j][i].getstatus() == 0) {
					consolewritesymbol(' ', 1);
				}
				else {
					consolewritesymbol('*', 1);
				}
			}
			else {
				if (Owner.field[j][i].getstatus() == 0) {
					consolewritesymbol('K', 1);
				}
				else {
					consolewritesymbol('X', 1);
				}
			}
		}
		consolewritesymbol('|', 1);
		consolewritesymbol('\n', 1);

	}

}

void consolewritefields(Gamer Owner, Gamer Enemy) {
	for (int i = 0; i < 20; i++) {
		cout << "*";
	}
	cout << "\n";
	consolewritesymbol(' ', 2);
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		consolewritesymbol(' ', 1);
		consolewritesymbol('A' + i, 1);
	}
	consolewritesymbol(' ', 8);
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		consolewritesymbol(' ', 1);
		consolewritesymbol('A' + i, 1);
	}
	cout << " \n";
	consolewritesymbol(' ', 2);
	consolewritesymbol('_', 21);
	consolewritesymbol(' ', 7);
	consolewritesymbol('_', 21);
	cout << "\n";
	for (int i = 0; i < SIZE_OF_FIELD; i++) {
		if (i < 9) {
			consolewritesymbol('1' + i, 1);
			consolewritesymbol(' ', 1);
		}
		else {
			consolewritesymbol('1', 1);
			consolewritesymbol('0' + i - 9, 1);
		}
		for (int j = 0; j < SIZE_OF_FIELD; j++) {
			consolewritesymbol('|', 1);
			if (Owner.field[j][i].getship() == nullptr) {
				if (Owner.field[j][i].getstatus() == 0) {
					consolewritesymbol(' ', 1);
				}
				else {
					consolewritesymbol('*', 1);
				}
			}
			else {
				if (Owner.field[j][i].getstatus() == 0) {
					consolewritesymbol('K', 1);
				}
				else {
					consolewritesymbol('X', 1);
				}
			}
		}
		consolewritesymbol('|', 1);
		consolewritesymbol(' ', 5);
		if (i < 9) {
			consolewritesymbol('1' + i, 1);
			consolewritesymbol(' ', 1);
		}
		else {
			consolewritesymbol('1', 1);
			consolewritesymbol('0', 1);
		}
		for (int j = 0; j < SIZE_OF_FIELD; j++) {
			consolewritesymbol('|', 1);
			if (Enemy.field[j][i].getstatus() == 0) {
				consolewritesymbol(' ', 1);
			}
			else {
				if (Enemy.field[j][i].getship() == nullptr) {
					consolewritesymbol('*', 1);
				}
				else {
					consolewritesymbol('X', 1);
				}
			}
		}
		consolewritesymbol('|', 1);
		consolewritesymbol('\n', 1);

	}

}