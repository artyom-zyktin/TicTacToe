#ifndef PLAYER_H
#define PLAYER_H

#include "Field.h"

#include <string>

class Player
{
public:
	Player(Field* field, Marker marker, std::string name);

	virtual void MakeMove(int i, int j);

	std::string& GetName();
	Marker GetMarker();

protected:

	Field* _field;
	Marker _marker;
	std::string _name;

private:
};

class Bot : public Player
{
public:
	Bot(Field* field, Marker marker);
	virtual void MakeMove(int i, int j) override;
};

#endif//PLAYER_H

