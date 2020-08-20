#ifndef DRIVER_H
#define DRIVER_H

#include "Player.h"
#include "View.h"
#include "Player.h"
#include "Field.h"

#include <typeinfo>

#include <iostream>

template<class TView, class TPlayer1, class TPlayer2>
class Driver
{
	static_assert(std::is_base_of<View, TView>::value);
	static_assert(std::is_base_of<Player, TPlayer1>::value);
	static_assert(std::is_base_of<Player, TPlayer2>::value);

public:
	Driver();

	void Go();

protected:
	Field* _field;
	TView* _view;
	TPlayer1* _player1;
	TPlayer2* _player2;

	Player* _getCurrentPlayer();
	void _setCurrentPlayer(FirstPlayer first_pLayer);

private:
	Player* _current_player;

};

template<class TView, class TPlayer1, class TPlayer2>
inline Driver<TView, TPlayer1, TPlayer2>::Driver()
	: _field(new Field), _view(new TView()), _player1(new TPlayer1()), _player2(new TPlayer2())
{
	_view->SetField(_field);

	_player1->SetField(_field);
	_player2->SetField(_field);
}

template<class TView, class TPLayer1, class TPlayer2>
inline void Driver<TView, TPLayer1, TPlayer2>::Go()
{
	std::cout << "1\n";

	_setCurrentPlayer(_view->GetFirstPLayer());

	std::cout << "2\n";

	_getCurrentPlayer()->SetName(_view->GetString("Set name of firast player"));
	_getCurrentPlayer()->SetName(_view->GetString("Set name of second player"));

	std::cout << "3\n";

	Player* _player = _getCurrentPlayer();
	_player->SetMarker(_view->GetMarker(_player->GetName()));

	std::cout << "4\n";

	_player = _getCurrentPlayer();
	_player->SetMarker(_view->GetMarker(_player->GetName()));

	std::cout << "5\n";

	_view->ShowMessage(_field->GetState() == State::draw ? "Draw" :
		_field->GetState() == State::x_win ? "X win" :
		_field->GetState() == State::o_win ? "O win" :
		_field->GetState() == State::in_game ? "in game" : "Error");

	while (_field->GetState() == State::in_game)
	{
		std::cout << "5.1\n";
		_player = _getCurrentPlayer();
		std::cout << "5.2\n";
		if (typeid(_player) == typeid(Bot)) _player->MakeMove(0, 0);
		else
		{
			std::cout << "5.3.1\n";
			Coords _coords = _view->GetCoords();
			_player->MakeMove(_coords.i, _coords.j);
			std::cout << "5.3.2\n";
		}
	}

	std::cout << "6\n";

	_view->ShowMessage(_field->GetState() == State::draw ? "Draw" :
		_field->GetState() == State::x_win ? "X win" :
		_field->GetState() == State::o_win ? "O win" : "Error");

	std::cout << "7\n";
}

template<class TView, class TPLayer1, class TPlayer2>
inline Player* Driver<TView, TPLayer1, TPlayer2>::_getCurrentPlayer()
{
	if (_current_player == _player1)
	{
		_current_player = _player2;
		return _player2;
	}
	else
	{
		_current_player = _player1;
		return _player1;
	}
}

template<class TView, class TPLayer1, class TPlayer2>
inline void Driver<TView, TPLayer1, TPlayer2>::_setCurrentPlayer(FirstPlayer first_pLayer)
{
	switch (first_pLayer)
	{
	case FirstPlayer::player_1:
		_current_player = _player1;
		break;
	case FirstPlayer::player_2:
		_current_player = _player2;
		break;
	}
}


#endif//DRIVER_H