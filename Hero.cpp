#include "Hero.h"

Hero::Hero()
{
	x = 0;
	y = 0;
	hitpoints = 100;
	for (int i = 0; i < 10; i++)
		inventory[i] = 0;
	invisible = 0;
}

wstring Hero::move(char _dir, Map* _map)
{
	wchar_t door = _map->connected[x][y][0][0];
	bool moved = false;
	if (_dir == 'w' && _map->connected[x][y][0][1] == 'c' && !(door == 'e' || door == 's' || door == 'w'))		// If I want to go North and the maze lets me go north, and its not a door blocking me then go north
	{
		_map->visibleMap[x--][y] = _map->pickChar(x, y);
		moved = true;
	}
	else if (_dir == 'd' && _map->connected[x][y][1][2] == 'c' && !(door == 'n' || door == 's' || door == 'w'))	// East
	{
		_map->visibleMap[x][y++] = _map->pickChar(x, y);
		moved = true;
	}
	else if (_dir == 's' && _map->connected[x][y][2][1] == 'c' && !(door == 'n' || door == 'e' || door == 'w'))	// South
	{
		_map->visibleMap[x++][y] = _map->pickChar(x, y);
		moved = true;
	}
	else if (_dir == 'a' && _map->connected[x][y][1][0] == 'c' && !(door == 'n' || door == 'e' || door == 's'))	// West
	{
		_map->visibleMap[x][y--] = _map->pickChar(x, y);
		moved = true;
	}
	if (moved)
	{
		if (invisible > 0)
			invisible--;
		if (_map->connected[x][y][2][0] != 'u' && invisible == 0)
			return L"trivia time. answer the question.";
		if (!(_map->connected[x][y][0][0] == 'h' || _map->connected[x][y][0][0] == 'n' || _map->connected[x][y][0][0] == 'e' || _map->connected[x][y][0][0] == 's' || _map->connected[x][y][0][0] == 'w'))		// if you are on a key
		{
			for (int i = 0; i < 10; i++)
				if (inventory[i] == 0)
				{
					inventory[i] = (int)(_map->connected[x][y][0][0]);
					_map->connected[x][y][0][0] = 'h';
					return L"you picked up a key.";
				}
			return L"your inventory is full. you cannot pick up this key.";
		}
		if (_map->connected[x][y][0][2] != 'u')
		{
			for (int i = 0; i < 10; i++)
				if (inventory[i] > 0 && ((char)inventory[i]) == _map->connected[x][y][0][2])
				{
					_map->connected[x][y][0][2] = 'u';
					_map->connected[x][y][0][0] = 'h';
					inventory[i] = 0;
					return L"you have unlocked a door.";
				}
			return L"you need a key for this door.";
		}
		if (_map->connected[x][y][2][2] != 'u')
		{
			for (int i = 0; i < 10; i++)
				if (inventory[i] == 0)
					if (_map->connected[x][y][2][2] == 'h')
					{
						inventory[i] = -2;
						_map->connected[x][y][2][2] = 'u';
						return L"you picked up a health potion";
					}
					else
					{
						inventory[i] = -1;
						_map->connected[x][y][2][2] = 'u';
						return L"you picked up an invisibility potion";
					}
			return L"your inventory is full. you cannot pick up this potion";
		}
	} else return L"you can't move in that direction.";
	return L"";
}

wstring Hero::useInventory(int _slot)
{
	switch (inventory[_slot])
	{
	case -2:
		if (hitpoints == 100)
			return L"you are already at full health";
		hitpoints += 5;
		inventory[_slot] = 0;
		return L"you used a health potion";
		break;
	case -1:
		invisible += 10;
		inventory[_slot] = 0;
		return L"you used an invisibility potion. you are now invisible for " + to_wstring(invisible) + L" moves";
		break;
	case 0:
		return L"that inventory slot is empty";
		break;
	default:
		return L"this is key #" + to_wstring(inventory[_slot]) + L". find the matching door to use it";
		break;
	}
}