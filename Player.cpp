#include "Player.h"

Player::Player(Field* field, Marker marker, std::string name)
	: _field(field), _marker(marker), _name(name)
{
}

void Player::MakeMove(int i, int j)
{
	_field->SetMarker(_marker, i, j);
}

std::string& Player::GetName()
{
	return _name;
}

Marker Player::GetMarker()
{
	return _marker;
}

Bot::Bot(Field* field, Marker marker)
	: Player(field, marker, "AI")
{
}
