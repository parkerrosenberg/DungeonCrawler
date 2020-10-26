#pragma once
#ifndef HERO_H
#define HERO_H
#include "Map.h"
using namespace std;

class Hero
{
public:
	int x;
	int y;
	int hitpoints;
	int inventory[10];		// -2 = health pot, -1 = invis pot		// 0 is nothing		// 1, 2, 3, ... = keys
	int invisible;

	Hero();
	wstring move(char, Map*);
	wstring useInventory(int);
};
#endif