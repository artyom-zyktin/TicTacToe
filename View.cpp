#include "View.h"

#include <iostream>

View::View()
	: _field(nullptr)
{
}

View::~View()
{
}

void View::SetField(Field* new_field)
{
	_field = new_field;
}

void View::Show()
{
	std::cout << "Tic Tac Toe !!!" << std::endl;
}

void View::DrawField()
{
	if (_field == nullptr) return;

    const char ** _cells = _field->GetCells();

	for (int _i = 0; _i < 3; _i++)
	{
		for (int _j = 0; _j < 3; _j++) std::cout << _cells[_i][_j];
		std::cout << std::endl;
	}

	switch (_field->GetState())
	{
	case State::in_game:
		std::cout << "\nIn game\n";
		break;
	case State::draw:
		std::cout << "\nDraw\n";
		break;
	case State::o_win:
		std::cout << "\nO wins\n";
		break;
	case State::x_win:
		std::cout << "\nX wins\n";
		break;
	}		         
}

void View::ShowMessage(const std::string& message)
{
	std::cout << message << std::endl;
}

FirstPlayer View::GetFirstPLayer()
{
	/*using namespace std;

	cout << "Choose first player (1 or 2): ";

	string _player_n;
	
	cin >> _player_n;

	cout << _player_n << endl;

	if ((_player_n != "1") || _player_n != "2")
	{
		cout << "Player num must be '1' or '2'\n";
		return GetFirstPLayer();
	}

	return _player_n == "2" ? FirstPlayer::player_1 : FirstPlayer::player_2;*/
	return FirstPlayer::player_1;
}

Marker View::GetMarker(const std::string& player_name)
{
	using namespace std;

	string _s_marker;
	cout << "Marker for " << player_name << " ('x' or 'o'): ";
	cin >> _s_marker;

	return _s_marker == "x" ? Marker::x :
		   _s_marker == "o" ? Marker::o :
		   GetMarker(player_name);
}

std::string View::GetString(const std::string& message)
{
	std::string _input_string;
	std::cout << message << ": "; std::cin >> _input_string;

	return _input_string;
}

Coords View::GetCoords()
{
	Coords _c;
	std::cout << "set marker at: "; std::cin >> _c.i; std::cin >> _c.j;
	return _c;
}
