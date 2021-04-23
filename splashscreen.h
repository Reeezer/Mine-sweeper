#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QtWidgets>

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

signals:
    void easy();
    void medium();
    void hard();
};
#endif // SPLASHSCREEN_H
