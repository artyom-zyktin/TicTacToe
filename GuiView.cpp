#include "GuiView.h"

#include "QVBoxLayout"
#include "QHBoxLayout"

#include <QInputDialog>
#include <QMessageBox>

#include <QEventLoop>

#include <QDebug>

GuiView::GuiView(QWidget *parent) : QWidget(parent), View(), _buttons(new QPushButton**[3]), _lbl(new QLabel(this)), _tmp_coords({-1, -1})
{
    _initGUI();
}

void GuiView::_initGUI()
{

    setFixedSize(300, 300);

    auto _mainVBox = new QVBoxLayout(this);
    setLayout(_mainVBox);

    auto _hboxes = new QHBoxLayout*[4];

    for (int _i = 0; _i < 4; ++_i)
    {
        _hboxes[_i] = new QHBoxLayout(this);
        _mainVBox->addLayout(_hboxes[_i]);
    }

    _lbl->setText(tr("Tic Tac Toe!"));

    _hboxes[0]->addWidget(_lbl, 1, Qt::AlignCenter);

    for (int _i = 0; _i < 3; ++_i)
    {
        _buttons[_i] = new QPushButton*[3];

        for (int _j = 0; _j < 3; ++_j)
        {
            _buttons[_i][_j] = new QPushButton(this);
            _buttons[_i][_j]->setFixedSize(30, 30);
            connect(_buttons[_i][_j], &QPushButton::clicked, this, &GuiView::_set_tmp_coords);
            _hboxes[_i+1]->addWidget(_buttons[_i][_j], 1, Qt::AlignCenter);
        }
    }
}

void GuiView::Show()
{
    show();
}

void GuiView::DrawField()
{
    auto _cells = _field->GetCells();
    for (int _i = 0; _i < 3; ++_i) for (int _j = 0; _j < 3; ++_j)
    {
        if (_cells[_i][_j] == 'x')
        {
            _buttons[_i][_j]->setStyleSheet("QPushButton {color: red;}");
            _buttons[_i][_j]->setText(tr("X"));
            _buttons[_i][_j]->setDisabled(true);
        }
        if (_cells[_i][_j] == 'o')
        {
            _buttons[_i][_j]->setStyleSheet("QPushButton {color: blue;}");
            _buttons[_i][_j]->setText(tr("O"));
            _buttons[_i][_j]->setDisabled(true);
        }
    }

    auto _state = _field->GetState();
    if (_state != State::in_game)
    {
        QString _str;
        switch (_state) {
            case State::draw:
                _str = "Draw";
                break;
        case State::x_win:
                _str = "X win";
                break;
        case State::o_win:
                _str = "O win";
                break;
        }

        QMessageBox _msgBox("Game over", _str, QMessageBox::NoIcon, 1, 0, 0, this);
        _msgBox.exec();
    }
}

Coords GuiView::GetCoords()
{
    Coords _move;

    QEventLoop l;

    for (int _i = 0; _i < 3; ++_i) for (int _j = 0; _j < 3; ++_j)
    {
        connect(_buttons[_i][_j], &QPushButton::clicked, &l, &QEventLoop::quit);
    }

    l.exec();

            _move.i = _tmp_coords.i; _move.j = _tmp_coords.j;
            _tmp_coords.i = -1; _tmp_coords.j = -1;

    return _move;
}

Marker GuiView::GetMarker(const std::string& player_name)
{
    QMessageBox _msgBox("Choose marker for...", QString(player_name.c_str()), QMessageBox::NoIcon, 0, 0, 0, this);
    QAbstractButton* _xBtn = _msgBox.addButton("X! Yeah!", QMessageBox::NoRole);
    _msgBox.addButton("O! Cool!", QMessageBox::NoRole);

    _msgBox.exec();

    if (_msgBox.clickedButton() == _xBtn)
    {
        qDebug() << "X\n";
        return Marker::x;
    }
    else return Marker::o;
}

void GuiView::ShowMessage(const std::string &message)
{
    QMessageBox _msgBox("I have smth for you...", QString(message.c_str()), QMessageBox::NoIcon, QMessageBox::Ok, 0, 0, this);
    _msgBox.setModal(true);
    _msgBox.show();
}

FirstPlayer GuiView::GetFirstPlayer()
{
    QMessageBox _msgBox("Choose first... ", "player", QMessageBox::NoIcon, 0, 0, 0, this);
    QAbstractButton* _firstBtn = _msgBox.addButton("player 1", QMessageBox::NoRole);
    _msgBox.addButton("player 2", QMessageBox::NoRole);

    _msgBox.exec();

    if (_msgBox.clickedButton() == _firstBtn) return FirstPlayer::player_2;
    else return FirstPlayer::player_1;
}

std::string GuiView::GetString(const std::string &message)
{
    std::string _result;

    do
    {
        bool _ok;
        _result = QInputDialog().getText(this,
                                         "I need smth from you...",
                                          QString(message.c_str()),
                                          QLineEdit::Normal, "", &_ok).toStdString();

        if (_ok) break;
    } while (true);

    return _result;
}

void GuiView::_set_tmp_coords()
{
    auto _sender = sender();
    for (int _i = 0; _i < 3; ++_i) for (int _j = 0; _j < 3; ++_j)
    {
        if (_sender == _buttons[_i][_j])
        {
            _tmp_coords.i = _i; _tmp_coords.j = _j;
        }
    }
}
