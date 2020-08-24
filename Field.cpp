#include "Field.h"

Field::Field()
    : _cells(new char*[3])
{
    _cells[0] = new char[3];
    _cells[1] = new char[3];
    _cells[2] = new char[3];

	for (int _i = 0; _i < 3; ++_i) for (int _j = 0; _j < 3; ++_j) _cells[_i][_j] = '-';
}

Field::Field(const Field& other)
    : _cells(new char*[3])
{
    _cells[0] = new char[3];
    _cells[1] = new char[3];
    _cells[2] = new char[3];

    for (int _i = 0; _i < 3; ++_i) for (int _j = 0; _j < 3; ++_j) _cells[_i][_j] = other._cells[_i][_j];
}

Field::~Field()
{
    delete[] _cells[0];
    delete[] _cells[1];
    delete[] _cells[2];

    delete[] _cells;
}

State Field::GetState() const
{
	return _isWin(Marker::x) ? State::x_win   :
	       _isWin(Marker::o) ? State::o_win   :
		   _hasEmptyCells()  ? State::in_game :
		   State::draw;
}

void Field::SetMarker(Marker marker, int i, int j)
{
	char _marker = _marker2Char(marker);
	_cells[i][j] = _marker;
}

char const** Field::GetCells() const
{
    return const_cast<char const **>(_cells);
}

bool Field::_hasEmptyCells() const
{
	for (int _i = 0; _i < 3; ++_i)
		for (int _j = 0; _j < 3; ++_j) if (_cells[_i][_j] == '-') return true;

	return false;
}

bool Field::_isWin(Marker marker) const
{
	char _marker = _marker2Char(marker);

	if (_cells[0][0] == _marker && _cells[0][1] == _marker && _cells[0][2] == _marker) return true;
	if (_cells[1][0] == _marker && _cells[1][1] == _marker && _cells[1][2] == _marker) return true;
	if (_cells[2][0] == _marker && _cells[2][1] == _marker && _cells[2][2] == _marker) return true;

	if (_cells[0][0] == _marker && _cells[1][0] == _marker && _cells[2][0] == _marker) return true;
	if (_cells[0][1] == _marker && _cells[1][1] == _marker && _cells[2][1] == _marker) return true;
	if (_cells[0][2] == _marker && _cells[1][2] == _marker && _cells[2][2] == _marker) return true;

	if (_cells[0][0] == _marker && _cells[1][1] == _marker && _cells[2][2] == _marker) return true;
	if (_cells[2][0] == _marker && _cells[1][1] == _marker && _cells[0][2] == _marker) return true;

	return false;
}
