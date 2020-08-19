#ifndef FIELD_H
#define FIELD_H

enum class Marker
{
	o, x
};

enum class State
{
	in_game, draw, x_win, o_win
};

class Field
{
public:
	Field();
	~Field();

	State GetState();

	void SetMarker(Marker marker, int i, int j);

	char const** GetCells();

protected:

	virtual bool _hasEmptyCells();
	virtual bool _isWin(Marker marker);

private:

	char** _cells;

	inline char _marker2Char(Marker marker) { return marker == Marker::x ? 'x' : 'o'; }
};

#endif//FIELD_H

