#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QtWidgets>
#include "button.h"

class GameView : public QWidget
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr, int size = 1);
    ~GameView();
    void updateDisplay();

public slots:
    void decreaseBombs();
    void gameOver();
    void checkFlag();
    void floodFill();

signals:
    void displaySplashScreen();

protected:
    void fillBombs();
    void initialize();

    QList<Button *> *_buttonList;
    int _size;
    int _nbBombs;
    QGridLayout *_mapGridLayout;
    QLabel *_nbBombsLabel;
};

#endif // GAMEVIEW_H
