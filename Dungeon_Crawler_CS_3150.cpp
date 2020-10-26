/*
 * Trevor Cheney
 * Parker Rosenberg
 * CS 3150
 * Dr. Cantrell
 * 
 * 
 * Code Quality (including user interface)			you decide
 * Logical use of multiple files					there are six files
 * Overall Functionality (Could I break it)			good luck
 * Logical use of enum type							an answers declared enum in main.h for the trivia questions
 * Proper use of extern variable					We could not find a legitimate use for extern anywhere. I feel like if you use proper class structure, it just isn't necessary
 * Proper use of static variable					mapH and mapW are static in map.h
 * Logical use of a struct							we used classes instead. There are two classes
 * Logical use of random number generator			random numbers are all throughout, just do a ctrl-f for rand(). There are 9 occurences
 */
#include "Main.h"

using namespace std;

int main()
{
	wcout << _setmode(_fileno(stdout), _O_U16TEXT) << endl;				// Lets the program use unicode characters
	srand(time(0));														// Random seed

	#pragma region Randomize trivia array
	int random;
	for (int i = 0; i < 30; i++)
	{
		do {
			random = rand() % 30;
		} while (triviaInitial[random][0] == L"U");
		for (int j = 0; j < 6; j++)
		{
			trivia[i][j] = triviaInitial[random][j + 1];
		}
		triviaInitial[random][0] = L"U";
	}
#pragma endregion
	Map* map = new Map();
	Hero* hero = new Hero();

	char selection = 'a';														// user input variable
	wstring message;

	printGrid(false, hero, map);
	wcout << L"you have entered the labyrinth... " << endl;
	while (selection != 'q')
	{
		cin >> selection;
		if(map->connected[hero->x][hero->y][2][0] == 'u' || hero->invisible > 0)
			switch (selection)
			{
			case 'w':
			case 'a':
			case 's':
			case 'd':
				message = hero->move(selection, map);
				if(hero->invisible > 0)
					message += L" you have " + to_wstring(hero->invisible) + L" more moves while invisible.";
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				selection -= 48;
				message = hero->useInventory(selection);
				break;
			default:
				message = L"invalid selection.";
			}
		else
		{
			answers ans = A;
			switch (trivia[triviaIndex][1].at(0))
			{
			case 'a':
				ans = A;
				break;
			case 'b':
				ans = B;
				break;
			case 'c':
				ans = C;
				break;
			case 'd':
				ans = D;
				break;
			}
			switch (selection)
			{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
				if (selection == trivia[triviaIndex][0].at(0))
					message = L"you answered correctly.";
				else
				{
					message = L"you answered incorrectly, the correct answer was " + trivia[triviaIndex][ans + 2] + L" you have lost 10 hp.";
					hero->hitpoints -= 10;
				}
				map->connected[hero->x][hero->y][2][0] = 'u';
				triviaIndex++;
				break;
			default:
				message = L"invalid input.";
			}
		}

		if (hero->hitpoints <= 0) { for (int i = 0; i < 37; i++) wcout << sadpepe[i] << endl; exit(0); }
		if (hero->x == Map::mapH - 1 && hero->y == Map::mapW - 1) { for (int i = 0; i < 11; i++) wcout << poggers[i] << endl; exit(0); }
		printGrid(false, hero, map);
		wcout << message << endl;
	}
}

extern void printGrid(bool _full, Hero* _hero, Map* _map)
{
	int herox = _hero->x;						// this gets referenced a lot, so we'll save it here.
	int heroy = _hero->y;
	#pragma region print top border
	wcout << L'\x250c';//┌						// prints the top left corner of the grid
	for (int i = 0; i < Map::mapW; i++)			// prints the top border of the grid
		wcout << L'\x2500';//─
	wcout << L'\x2510' << endl;//┐				// prints top right corner
#pragma endregion
	#pragma region Prints Center
	if (!_full)
		for (int i = 0; i < Map::mapH; i++)											// Prints the middle section of the grid
		{																			// Also lets the hero see one square away, if not blocked by walls
			wcout << L'\x2502';//│
			if (i == herox - 1)
				for (int j = 0; j < Map::mapW; j++)
					if (j == heroy && _map->connected[herox][heroy][0][1] == 'c' && (_map->connected[herox][heroy][0][0] == 'h' || _map->connected[herox][heroy][0][0] == 'n'))
						wcout << _map->pickChar(i, j);
					else
						wcout << _map->visibleMap[i][j];
			else if (i == herox + 1)
				for (int j = 0; j < Map::mapW; j++)
					if (j == heroy && _map->connected[herox][heroy][2][1] == 'c' && (_map->connected[herox][heroy][0][0] == 'h' || _map->connected[herox][heroy][0][0] == 's'))
						wcout << _map->pickChar(i, j);
					else
						wcout << _map->visibleMap[i][j];
			else if (i == herox)
				for (int j = 0; j < Map::mapW; j++)
					if (j == heroy - 1 && _map->connected[herox][heroy][1][0] == 'c' && (_map->connected[herox][heroy][0][0] == 'h' || _map->connected[herox][heroy][0][0] == 'w'))
						wcout << _map->pickChar(i, j);
					else if (j == heroy)
						wcout << L'\x1d25';//ᴥ
					else if (j == heroy + 1 && _map->connected[herox][heroy][1][2] == 'c' && (_map->connected[herox][heroy][0][0] == 'h' || _map->connected[herox][heroy][0][0] == 'e'))
						wcout << _map->pickChar(i, j);
					else
						wcout << _map->visibleMap[i][j];
			else
				for (int j = 0; j < Map::mapW; j++)
					wcout << _map->visibleMap[i][j];
			wcout << L'\x2502';//│
			if (_map->connected[herox][heroy][2][0] != 'u' && i < 5 && _hero->invisible == 0)
					wcout << trivia[triviaIndex][i+1];
			wcout << endl;
		}
	else																			// Prints whole schebang
		for (int i = 0; i < Map::mapH; i++)
		{
			wcout << L'\x2502';//│
			for (int j = 0; j < Map::mapW; j++)
				wcout << _map->pickChar(i, j);
			wcout << L'\x2502' << endl;//│
		}
	#pragma endregion
	#pragma region print bottom border
	wcout << L'\x2514';//└						// prints bottom left corner
	for (int i = 0; i < Map::mapW; i++)			// prints bottom border
		wcout << L'\x2500';//─
	wcout << L'\x2518' << endl;//┘				// prints bottom right corner
#pragma endregion
	#pragma region Print inventory
	for (int i = 0; i < (Map::mapW - 24) / 2; i++)
		wcout << " ";
	wcout << "HP: ";								
	for (int i = 0; i < _hero->hitpoints/5; i++)
		wcout << L'\x2588';//█
	wcout << endl;

	for (int i = 0; i < (Map::mapW - 33) / 2; i++)
		wcout << " ";
	for (int i = 0; i < 10; i++)
		wcout << "  " << i;
	wcout << endl;

	for (int i = 0; i < (Map::mapW - 31) / 2; i++)
		wcout << " ";
	// ┏━━┯━━┯━━┯━━┯━━┯━━┯━━┯━━┯━━┯━━┓
	wcout << otherChars[0][0] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][1] << otherChars[2][1] << otherChars[2][1] << otherChars[0][2] << endl;
	
	for (int i = 0; i < (Map::mapW - 31) / 2; i++)
		wcout << " ";
	wcout << otherChars[2][0];
	for (int i = 0; i < 10; i++)
	{
		switch (_hero->inventory[i])
		{
		case -2:
			wcout << "HP";
			break;
		case -1:
			wcout << "IP";
			break;
		case 0:
			wcout << "  ";
			break;
		case 1:
			wcout << L'\x2776' << L'\x2556';
			break;
		case 2:
			wcout << L'\x2777' << L'\x2556';
			break;
		case 3:
			wcout << L'\x2778' << L'\x2556';
			break;
		case 4:
			wcout << L'\x2779' << L'\x2556';
			break;
		case 5:
			wcout << L'\x277a' << L'\x2556';
			break;
		case 6:
			wcout << L'\x277b' << L'\x2556';
			break;
		case 7:
			wcout << L'\x277c' << L'\x2556';
			break;
		case 8:
			wcout << L'\x277d' << L'\x2556';
			break;
		case 9:
			wcout << L'\x277e' << L'\x2556';
			break;
		case 10:
			wcout << L'\x277f' << L'\x2556';
			break;
		default:
			wcout << "you broke it" << endl;
		}
		if(i != 9)
			wcout << otherChars[2][2];
	}
	wcout << otherChars[2][0] << endl;

	for (int i = 0; i < (Map::mapW - 31) / 2; i++)
		wcout << " ";
	// ┗━━┷━━┷━━┷━━┷━━┷━━┷━━┷━━┷━━┷━━┛
	wcout << otherChars[1][0] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][1] << otherChars[2][1] << otherChars[2][1] << otherChars[1][2] << endl;
	#pragma endregion
}