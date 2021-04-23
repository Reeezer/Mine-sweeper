#include "button.h"

Button::Button(QWidget *parent, int x, int y)
    :QPushButton(parent), _x(x), _y(y)
{
    initialize();
}

Button::~Button()
{}

void Button::initialize()
{
    _flag = false;
    _bomb = false;
    _nbBombNearBy = 0;
    setText("");
    setIcon(QIcon(""));
    setFont(QFont("GROBOLD", 20));
    setIconSize(QSize(width(), height()));
}

int Button::getX() { return _x; }
int Button::getY() { return _y; }

void Button::displayText()
{
    setIcon(QIcon(""));
    setText("");

    if (_bomb)
        setIcon(QIcon(":/res/bomb.png"));
    else if (_nbBombNearBy != 0)
        setText(QString::asprintf("%d", _nbBombNearBy));
}

void Button::mousePressEvent(QMouseEvent *event)
{
    setText("");
    setIcon(QIcon(""));

    if (event->button() == Qt::RightButton) {
        if (isEnabled()) {
            _flag = !_flag;
            if (_flag)
                setIcon(QIcon(":/res/flag.png"));
            emit rightClick();
        }
    }
    else if (event->button() == Qt::LeftButton) {
        leftClicked();
    }
}

void Button::leftClicked()
{
    emit leftClick();
    setEnabled(false);
    if (_nbBombNearBy != 0)
        setText(QString::asprintf("%d", _nbBombNearBy));
    else if (_bomb) {
        setIcon(QIcon(":/res/bomb.png"));
        emit gameOver();
    }
    else if (_nbBombNearBy == 0 && !_bomb){
        emit empty();
    }
}

void Button::setBomb() { _bomb = true; _nbBombNearBy = 0; }
void Button::increaseNbBomb() { _nbBombNearBy++; }

bool Button::getFlag() { return _flag; }
int Button::getNbBombNearBy() { return _nbBombNearBy; }
bool Button::getBomb() { return _bomb; }
