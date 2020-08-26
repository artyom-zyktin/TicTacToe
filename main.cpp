#include "Driver.h"
#include "Player.h"
#include "View.h"
#include "GuiView.h"

#include <QApplication>

int main(int argn, char** argv)
{


    QApplication app (argn, argv);

    Driver <GuiView, Player, Bot> d;

	d.Go();

    return app.exec();
}
