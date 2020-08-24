#ifndef VIEW_H
#define VIEW_H

#include <string>

#include "Field.h"

enum class FirstPlayer
{
	player_1, player_2
};

class View
{
public:
	
	View();
	virtual ~View();

	void SetField(Field* new_field);

	virtual void Show();

	virtual void DrawField();
	virtual void ShowMessage(const std::string& message);

	virtual FirstPlayer GetFirstPLayer();

	virtual Marker GetMarker(const std::string& player_name);
	virtual std::string GetString(const std::string& message);

	virtual Coords GetCoords();


protected:

	Field* _field;

};


#endif//VIEW_H

