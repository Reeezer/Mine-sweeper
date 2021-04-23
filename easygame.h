#ifndef EASYGAME_H
#define EASYGAME_H

#include <QtWidgets>
#include "gameview.h"

class EasyGame : public GameView
{
    Q_OBJECT

public:
    EasyGame(QWidget *parent = nullptr);
    ~EasyGame();
};

#endif // EASYGAME_H
