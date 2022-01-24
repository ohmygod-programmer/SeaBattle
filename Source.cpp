#include "SeaBattle.h" 
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	int count_of_rounds = 1;
	int First_Player_Type = 1; //0 - Player, 1 - Random;
	int Second_Player_Type = 1;
	try {
	for (int i = 1; i < argc; i++) {
		if (argv[i] == "-h" || argv[i] == "--help") {
			cout << "Parameters:\n - c --count\n" <<
				"Default : 1, Count of rounds\n" <<
				" - f --first\n" <<
				"Default : random, First Player Type\n" <<
				" - s --second\n" <<
				"Default : random, Second Player Type\n";
			return 0;
		}
		if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--count") == 0) {
			i++;
			count_of_rounds = atoi(argv[i]);
			continue;
		}
		if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i], "--first") == 0) {
			i++;
			if (argv[i] == "random") {
				First_Player_Type = 1;
			}
			else if (argv[i] == "console") {
				First_Player_Type = 0;
			}
			else throw;
			continue;
		}
		if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--second") == 0) {
			i++;
			if (argv[i] == "random") {
				First_Player_Type = 1;
			}
			else if (argv[i] == "console") {
				First_Player_Type = 0;
			}
			else throw;
			continue;
		}
	}
	}
	catch (exception) {
		cout << "Uncorrect parameters\n";
		throw;
	}
	srand(time(NULL));
	

	Gamer* Player1 = NULL;
	Gamer* Player2 = NULL;
	int wins1 = 0;
	int wins2 = 0;
	
	switch (First_Player_Type)
	{
	case 0:
		Player1 = new ConsoleGamer;
		cout << "Welcome to the Sea Battle!\n";
		cout << "Player1, please write your name:\n";
		cin >> Player1->name;
		break;

	case 1:
		Player1 = new RandomGamer;
		Player1->name = "Robot1";
		break;

	default:
		throw;
	}

	switch (Second_Player_Type)
	{
	case 0:
		Player2 = new ConsoleGamer;
		cout << "Welcome to the Sea Battle!\n";
		cout << "Player2, please write your name:\n";
		cin >> Player2->name;
		break;

	case 1:
		Player2 = new RandomGamer;
		Player2->name = "Robot2";
		break;

	default:
		throw;
	}

	for (int i = 0; i < count_of_rounds; i++) {
		if (First_Player_Type == 0) {
			cout << Player1->name << ", You should choise cells to one battleship, two cruisers, three destroyersand four Torpedo Boats\n";
		}
			
		Player1->initialize();

		if (Second_Player_Type == 0) {
			cout << Player2->name << ", you should choise cells to one battleship, two cruisers, three destroyersand four Torpedo Boats\n";
		}

		Player2->initialize();

		consolewritefields(*Player1, *Player2);


		Gamer* Leader = Player1;
		Gamer* Enemy = Player2;
		while (Player1->getcountofships() && Player2->getcountofships()) {
			cout << Leader->name << ", it's your turn\n";
			int res = Leader->Turn(Enemy);
			consolewritefields(*Player1, *Player2);
			if (res == 0) {
				cout << "Mimo\n";
				Gamer* buf = Leader;
				Leader = Enemy;
				Enemy = buf;
			}
			else if (res == 1) {
				cout << "Hit! Keep shooting...\n";
			}
			else if (res == 2) {
				cout << "KILL! Keep shooting...\n";
			}
			else {
				throw;
			}

		}
		if (Player1->getcountofships() == 0) {
			cout << Player1->name << " win this round.\n";
			wins1++;
		}
		else {
			cout << Player2->name << " win this round.\n";
			wins2++;
		}
	}
	if (wins1 > wins2) {
		cout << Player1->name << " is winner! He win " << wins1 <<
			" of " << count_of_rounds << " rounds.\n";
	}
	else if (wins1 < wins2) {
		cout << Player2->name << " is winner! He win " << wins2 <<
		" of " << count_of_rounds << " rounds.\n";
	}
	else {
		cout << "Draw!\n";
	}
  	return 0;
	
}