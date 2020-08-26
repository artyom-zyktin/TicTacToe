#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "View.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QThread>

class GuiView : public QWidget, public View
{
    Q_OBJECT
public:
    explicit GuiView(QWidget *parent = nullptr);

    virtual void Show();

    virtual void DrawField();
    virtual void ShowMessage(const std::string& message);

    virtual FirstPlayer GetFirstPlayer();

    virtual Marker GetMarker(const std::string& player_name);
    virtual std::string GetString(const std::string& message);

    virtual Coords GetCoords();

protected:

    void _initGUI();

    QPushButton*** _buttons;
    QLabel* _lbl;

private:

    Coords _tmp_coords;

    void _set_tmp_coords();

};

#endif // GUIVIEW_H
