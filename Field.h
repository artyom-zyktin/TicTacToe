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

struct Coords
{
    int i, j;
};

class Field
{
public:
	Field();
    Field(const Field& other);

    virtual ~Field();

    State GetState() const;

	void SetMarker(Marker marker, int i, int j);

    char const** GetCells() const;

protected:

    virtual bool _hasEmptyCells() const;
    virtual bool _isWin(Marker marker) const;

private:

    char** _cells;

    inline char _marker2Char(Marker marker) const { return marker == Marker::x ? 'x' : 'o'; }
};

#endif//FIELD_H

