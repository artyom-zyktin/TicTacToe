#ifndef PLAYER_H
#define PLAYER_H

#include "Field.h"

#include <string>

class Player
{
public:
	Player();
	virtual ~Player();

	virtual void MakeMove(int i, int j);

	void SetField(Field* field);
	Field const* GetField() const;

	void SetMarker(Marker marker);
	Marker GetMarker() const;

	void SetName(const std::string& name);
	std::string const & GetName() const;

protected:

	Field* _field;
	Marker _marker;
	std::string _name;

private:
};

class Bot : public Player
{
public:
    virtual void MakeMove(int i, int j);
protected:

private:
    virtual int _analys(const Field field, Marker player, Marker bot, Coords& out_coords);

    int _rateOfState(const State state, Marker marker);

};


#endif//PLAYER_H

