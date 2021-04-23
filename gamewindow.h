#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "splashscreen.h"
#include "gameview.h"

#include <QtWidgets>

class GameWindow : public QStackedWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void diplayGameEasy();
    void diplayGameMedium();
    void diplayGameHard();
    void displaySplashScreen();

private:
    SplashScreen *_splashScreen;
    GameView *_gameView;
};

#endif // GAMEWINDOW_H
