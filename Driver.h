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

    bool _second_player_is_bot;
    bool _first_player_is_bot;

};

template<class TView, class TPlayer1, class TPlayer2>
inline Driver<TView, TPlayer1, TPlayer2>::Driver()
    : _field(new Field), _view(new TView()), _player1(new TPlayer1()), _player2(new TPlayer2()),
      _second_player_is_bot(false), _first_player_is_bot(false)
{
	_view->SetField(_field);

	_player1->SetField(_field);
	_player2->SetField(_field);
}

template<>
inline Driver<View, Bot, Player>::Driver()
    : _field(new Field), _view(new View), _player1(new Bot), _player2(new Player),
      _second_player_is_bot(false), _first_player_is_bot(true)
{
    _view->SetField(_field);

    _player1->SetField(_field);
    _player2->SetField(_field);
}

template<>
inline Driver<View, Player, Bot>::Driver()
    : _field(new Field), _view(new View), _player1(new Player), _player2(new Bot),
      _second_player_is_bot(true), _first_player_is_bot(false)
{
    _view->SetField(_field);

    _player1->SetField(_field);
    _player2->SetField(_field);
}

#include <iostream>

template<class TView, class TPLayer1, class TPlayer2>
inline void Driver<TView, TPLayer1, TPlayer2>::Go()
{
    _view->Show();

    _player1->SetName(_view->GetString("Set name of player 1"));
    _player2->SetName(_view->GetString("Set name of player 2"));

    _player1->SetMarker(_view->GetMarker(_player1->GetName()));
    _player2->SetMarker(_player1->GetMarker() == Marker::x ? Marker::o : Marker::x);

    _setCurrentPlayer(_view->GetFirstPlayer());

    Player* _player;
    while (_field->GetState() == State::in_game)
    {
        _player = _getCurrentPlayer();

        _view->ShowMessage(_player->GetName()+ "'s move:\n");

        if ((_player == _player1 && _first_player_is_bot) || ((_player == _player2 && _second_player_is_bot)))
        {
            _player->MakeMove(0, 0);
        }
        else
        {
            Coords _move = _view->GetCoords();
            _player->MakeMove(_move.i, _move.j);
        }

        _view->DrawField();
    }
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
