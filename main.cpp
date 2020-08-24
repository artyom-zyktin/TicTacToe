#include "Driver.h"
#include "Player.h"
#include "View.h"

int main()
{
    Driver <View, Player, Bot> d;

	d.Go();

	return 0;
}
