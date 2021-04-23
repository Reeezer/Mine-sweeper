#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QWidget *parent = nullptr, int x = -1, int y = -1);
    ~Button();
    bool getFlag();
    int getNbBombNearBy();
    bool getBomb();
    void setBomb();
    void increaseNbBomb();
    void displayText();
    void initialize();
    int getX();
    int getY();
    void leftClicked();

protected:
    void mousePressEvent(QMouseEvent *);

signals:
    void gameOver();
    void rightClick();
    void leftClick();
    void empty();

private:
    int _x, _y;
    bool _flag;
    bool _bomb;
    int _nbBombNearBy;
};

#endif // BUTTON_H
