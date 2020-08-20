#include "Player.h"

Player::Player()
	: _field(nullptr), _marker(Marker::o), _name("Player")
{
}

Player::~Player()
{
}

void Player::MakeMove(int i, int j)
{
	if (_field == nullptr) return;

	_field->SetMarker(_marker, i, j);
}

void Player::SetField(Field* field)
{
	_field = field;
}

Field const* Player::GetField() const
{
	return _field;
}

void Player::SetName(const std::string& name)
{
	_name = name;
}

std::string const & Player::GetName() const
{
	return _name;
}

void Player::SetMarker(Marker marker)
{
	_marker = marker;
}

Marker Player::GetMarker() const
{
	return _marker;
}

