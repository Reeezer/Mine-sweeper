#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    resize(800, 600);

    setWindowTitle("Demineur");
    QFontDatabase::addApplicationFont(":/res/GROBOLD.ttf");

    _splashScreen = new SplashScreen(this);
    addWidget(_splashScreen);

    setCurrentWidget(_splashScreen);

    QObject::connect(_splashScreen, &SplashScreen::easy, this, &GameWindow::diplayGameEasy);
    QObject::connect(_splashScreen, &SplashScreen::medium, this, &GameWindow::diplayGameMedium);
    QObject::connect(_splashScreen, &SplashScreen::hard, this, &GameWindow::diplayGameHard);
}

GameWindow::~GameWindow()
{}

void GameWindow::displaySplashScreen()
{
    setCurrentWidget(_splashScreen);
    delete _gameView;
}

void GameWindow::diplayGameEasy()
{
    _gameView = new GameView(this, 10);
    QObject::connect(_gameView, &GameView::displaySplashScreen, this, &GameWindow::displaySplashScreen);
    addWidget(_gameView);
    setCurrentWidget(_gameView);
}

void GameWindow::diplayGameMedium()
{
    _gameView = new GameView(this, 15);
    QObject::connect(_gameView, &GameView::displaySplashScreen, this, &GameWindow::displaySplashScreen);
    addWidget(_gameView);
    setCurrentWidget(_gameView);
}

void GameWindow::diplayGameHard()
{
    _gameView = new GameView(this, 20);
    QObject::connect(_gameView, &GameView::displaySplashScreen, this, &GameWindow::displaySplashScreen);
    addWidget(_gameView);
    setCurrentWidget(_gameView);
}
