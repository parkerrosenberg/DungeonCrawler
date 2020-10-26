#pragma once
#ifndef MAP_H
#define MAP_H
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Map
{
public:
	static const int mapH = 21; // 21
	static const int mapW = 80; // 80

	wchar_t visibleMap[mapH][mapW];				// map that records where the hero has been
	char connected[mapH][mapW][3][3];			// a 2d array for each element in the map showing if a box connects to its neighbors
	#pragma region array of symbols used for the maze
	const wchar_t mazeSymbol[6][4] =
	{ // y 0        1         2         3
		{ 'n',		L'\x2550','n',		L'\x2588'	},	// 0
		{ L'\x2554',L'\x2566',L'\x2557','n'			},	// 1
		{ L'\x2560',L'\x256c',L'\x2563',L'\x2551'	},	// 2
		{ L'\x255a',L'\x2569',L'\x255d','n'			},	// 3
		{ L'\x02c5',L'\x02c2',L'\x028c',L'\x02c3'	},	// 4
		{ L'\x2568',L'\x255e',L'\x2565',L'\x2561'	}	// 5
	};													// x
	/*const wchar_t mazeSymbol[6][4] =
	{ y    0   1   2   3
	{ 'n', '═', 'n', '█' }, 0
	{ '╔', '╦', '╗', 'n' }, 1
	{ '╠', '╬', '╣', '║' }, 2
	{ '╚', '╩', '╝', 'n' }, 3
	{ '˅', '˂', 'ʌ', '˃' }  4
	{ '╨', '╞', '╥', '╡' }  5
	};                       x
	*/
#pragma endregion

	Map();
	wchar_t pickChar(int, int);
};
#endif