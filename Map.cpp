#include "Map.h"

Map::Map()
{
	// srand(time(0));					// Random seed
	#pragma region initialize connected array with 'u'
	for (int j = 0; j < mapW; j++)					// ̲0̲ ̲1̲ ̲2
		for (int i = 0; i < mapH; i++)				// 1 c 1| 0		// h = 'hunted', n,e,s,w = door directions, #'s = keys		// connected north		// #'s = door nums
			for (int k = 0; k < 3; k++)				// c v c│ 1		// connected west											// visited				// connected east
				for (int l = 0; l < 3; l++)			// t c i│ 2		// trivia													// connected south		// i = invis, h = health
					connected[i][j][k][l] = 'u';					// u = unloaded, unvisited, unhunted, unconnected
#pragma endregion
	#pragma region hunt and kill maze generator
	int x = 0;						// index starts in top left corner
	int y = 0;						// directions
	int dir;						//  1 
	bool done = false;				//4 ᴥ 2
	connected[x][y][0][0] = 'h';	//  3
	vector<int> buffer;				// holds available doors to place
	int index = 0;
	int key = 1;					// first key is 1

	do
	{
		do
		{
			dir = rand() % 4 + 1;												// pick a random direction

			if (dir == 1 && x > 0 && connected[x - 1][y][0][0] == 'u')			// if north is unvisited and not a wall
			{
				connected[x][y][0][1] = 'c';									// let the two indexes know that they are connected
				connected[x - 1][y][2][1] = 'c';
				connected[x - 1][y][0][0] = 'h';								// set the previous direction to where you came from
				x--;															// adjust x,y index
			}
			else if (dir == 2 && y < mapW - 1 && connected[x][y + 1][0][0] == 'u')	// if east is unvisited and not a wall
			{
				connected[x][y][1][2] = 'c';
				connected[x][y + 1][1][0] = 'c';
				connected[x][y + 1][0][0] = 'h';
				y++;
			}
			else if (dir == 3 && x < mapH - 1 && connected[x + 1][y][0][0] == 'u')	// if south is unvisited and not a wall
			{
				connected[x][y][2][1] = 'c';
				connected[x + 1][y][0][1] = 'c';
				connected[x + 1][y][0][0] = 'h';
				x++;
			}
			else if (dir == 4 && y > 0 && connected[x][y - 1][0][0] == 'u')		// if west is unvisited and not a wall
			{
				connected[x][y][1][0] = 'c';
				connected[x][y - 1][1][2] = 'c';
				connected[x][y - 1][0][0] = 'h';
				y--;
			}
		} while ((x > 0 && connected[x - 1][y][0][0] == 'u') || (y < mapW - 1 && connected[x][y + 1][0][0] == 'u') || (x < mapH - 1 && connected[x + 1][y][0][0] == 'u') || (y > 0 && connected[x][y - 1][0][0] == 'u')); // do while available spaces exist next to current index
		if (connected[x][y][0][0] == 'h' && rand() % 10 < 1 && key <= 10)
		{
			connected[x][y][0][0] = key;
			buffer.push_back(key++);	// 1, 2, 3, 4
		}
		//hunt
		// reset all vars
		bool north = false, east = false, south = false, west = false;
		for (int i = 0; i < mapH; i++) // row by row check starting from the top
		{
			for (int j = 0; j < mapW; j++)
			{
				if (connected[i][j][0][0] == 'u') // checking for empty squares
				{
					if (i > 0 && connected[i - 1][j][0][0] != 'u')			// that are next to loaded squares
						north = true;										// note the directions from the empty square to each adjacent loaded square
					if (j < mapW - 1 && connected[i][j + 1][0][0] != 'u')
						east = true;
					if (i < mapH - 1 && connected[i + 1][j][0][0] != 'u')
						south = true;
					if (j > 0 && connected[i][j - 1][0][0] != 'u')
						west = true;
					if (north || east || south || west) // if any of em found a hit
					{
						x = i; // save the location
						y = j;
						i = mapH; // exit the loop
						j = mapW;
						done = false; // we aint done baby
					}
				}
				else
					done = true; // nothing to hunt so far
			}
		}
		if (!done) // if there is still more to hunt
		{
			do
			{
				dir = rand() % 4 + 1;					// pick a direction

				if (dir == 1 && north)					// if you picked north and we can connect with north
				{
					connected[x][y][0][1] = 'c';		// connect them
					connected[x - 1][y][2][1] = 'c';
					connected[x][y][0][0] = 'h';		// This square has been hunted
				}
				else if (dir == 2 && east)
				{
					connected[x][y][1][2] = 'c';
					connected[x][y + 1][1][0] = 'c';
					connected[x][y][0][0] = 'h';
				}
				else if (dir == 3 && south)
				{
					connected[x][y][2][1] = 'c';
					connected[x + 1][y][0][1] = 'c';
					connected[x][y][0][0] = 'h';
				}
				else if (dir == 4 && west)
				{
					connected[x][y][1][0] = 'c';
					connected[x][y - 1][1][2] = 'c';
					connected[x][y][0][0] = 'h';
				}
				if (connected[x][y][0][0] == 'h' && index < key - 1 && buffer.at(index) != 0 && rand() % 3 < 1)
				{
					if (dir == 1) connected[x][y][0][0] = 'n';	// this square is a door blocking passage south
					if (dir == 2) connected[x][y][0][0] = 'e';
					if (dir == 3) connected[x][y][0][0] = 's';
					if (dir == 4) connected[x][y][0][0] = 'w';
					connected[x][y][0][2] = buffer.at(index++);
				}
			} while (connected[x][y][0][0] == 'u'); // ((dir == 1 && north) || (dir == 2 && east) || (dir == 3 && south) || (dir == 4 && west))); // while none of the if's above have been hit
		}
	} while (!done); // while there are still things to hunt
#pragma endregion
	#pragma region load the visible map with blank spaces
	for (int i = 0; i < mapH; i++)
		for (int j = 0; j < mapW; j++)
			visibleMap[i][j] = ' ';
#pragma endregion
	#pragma region load with potions and enemies
	int triviaCounter = 0;
	int hPotion = 0;
	int iPotion = 0;
	for (int i = 0; i < mapH; i++)
		for (int j = 0; j < mapW; j++)
		{
			if (!(rand() % 50) && triviaCounter < 30)		// Places trivia questions
			{
				connected[i][j][2][0] = 't';
				triviaCounter++;
			}
			if (!(rand() % 70))								// places health pots
			{
				connected[i][j][2][2] = 'h';
				hPotion++;
			}
			else if (!(rand() % 100))						// places invisibility pots
			{
				connected[i][j][2][2] = 'i';
				iPotion++;
			}
		}
	wcout << "Trivia: " << triviaCounter << endl;			// For debugging purposes
	wcout << "Health: " << hPotion << endl;
	wcout << "Invis: " << iPotion << endl;
	wcout << "Keys: " << key-1 << endl;
#pragma endregion
}

// finds the correct ascii character for each maze piece
wchar_t Map::pickChar(int _i, int _j)
{
	bool north = false, east = false, south = false, west = false;
	if (connected[_i][_j][0][1] == 'c') north = true;
	if (connected[_i][_j][1][2] == 'c') east = true;
	if (connected[_i][_j][2][1] == 'c') south = true;
	if (connected[_i][_j][1][0] == 'c') west = true;

	if (connected[_i][_j][0][0] != 'h')		// if its a door
	{
		if (connected[_i][_j][0][0] == 'n') return mazeSymbol[5][0];
		if (connected[_i][_j][0][0] == 'e') return mazeSymbol[5][1];
		if (connected[_i][_j][0][0] == 's') return mazeSymbol[5][2];
		if (connected[_i][_j][0][0] == 'w') return mazeSymbol[5][3];
	}

	if (north) {
		if (east){
			if (south) {
				if (west) { return mazeSymbol[2][1]; }		// NESW
				else { return mazeSymbol[2][0]; }			// NES
			}
			else if (west) { return mazeSymbol[3][1]; }		// NEW
			else { return mazeSymbol[3][0]; }				// NE
		}
		else if (south) {
			if (west) { return mazeSymbol[2][2]; }			// NSW
			else { return mazeSymbol[2][3]; }				// NS
		}
		else if (west) { return mazeSymbol[3][2]; }			// NW
		else {return mazeSymbol[4][0]; }					// N
	}
	else if (east) {
		if (south) {
			if (west) { return mazeSymbol[1][1]; }			// ESW
			else { return mazeSymbol[1][0]; }				// ES
		}
		else if (west) { return mazeSymbol[0][1]; }			// EW
		else { return mazeSymbol[4][1]; }					// E
	}
	else if (south) {
		if (west) { return mazeSymbol[1][2]; }				// SW
		else { return mazeSymbol[4][2]; }					// S
	}
	else if (west) { return mazeSymbol[4][3]; }				// W
	else { return mazeSymbol[0][3]; }						// unconnected (shouldn't happen i think)
}