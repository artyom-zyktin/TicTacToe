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


#include <iostream>
#include <vector>
#include <map>

int Bot::_analys(const Field field, Marker player, Marker bot, Coords& out_coords)
{

    using std::vector;
    using std::pair;

    using score = int;

    using Move = pair<Coords, score>;

    auto _state = field.GetState();
    if (player == bot && _state != State::in_game)
        return _rateOfState(_state, bot);
    if (player != bot && _state != State::in_game)
        return -_rateOfState(_state, player);

    vector<Coords> _empty_cells;
    const char** _cells = field.GetCells();
    for (int _i = 0; _i < 3; _i++) for (int _j = 0; _j < 3; _j++)
    {
        if (_cells[_i][_j] == '-') _empty_cells.push_back(Coords {_i, _j});
    }

    vector<Move> _moves;
    for (auto _empty_cell : _empty_cells)
    {
        Move _move;
        _move.first/*Coords*/ = _empty_cell;
        auto _new_field = field;
        _new_field.SetMarker(_marker, _move.first.i, _move.first.j);

        Bot _human;
        _human.SetField(&_new_field);

        Coords _new_move;
        if (player == bot)
        {
            _human.SetMarker(bot == Marker::x ? Marker::o : Marker::x);
            _move.second/*score*/ = _human._analys(_new_field, bot == Marker::x ? Marker::o : Marker::x, bot, _new_move);
        }
        else
        {
            _human.SetMarker(bot);
            _move.second/*score*/ = _human._analys(_new_field, bot, bot, _new_move);
        }

        _moves.push_back(_move);
    }

    Move _best_move;
    if (player == bot)
    {
        _best_move.second = -100500;
        for (auto _move : _moves)
        {
            if (_move.second > _best_move.second) _best_move = _move;
        }
    }
    else
    {
        _best_move.second = 100500;
        for (auto _move : _moves)
        {
            if (_move.second < _best_move.second) _best_move = _move;
        }
    }

    out_coords = _best_move.first;
    return _best_move.second;

}

int Bot::_rateOfState(State state, Marker marker)
{
    return state == State::draw ? 0 :
           (state == State::x_win && marker == Marker::x) || (state == State::o_win && marker == Marker::o) ? 1 : -1;
}

void Bot::MakeMove(int i, int j)
{
    Coords _move;
    _analys(*_field, _marker, _marker, _move);
    _field->SetMarker(_marker, _move.i, _move.j);
}

