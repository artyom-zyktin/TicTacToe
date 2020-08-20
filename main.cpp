#include "Driver.h"
#include "Player.h"
#include "View.h"

int main()
{
	Driver <View, Player, Player> d;

	d.Go();

	return 0;
}