#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("\
                    QWidget { background-color: #1F2833; }\
                    QLabel { background-color: rgba(0,0,0,0); color: white; font-size : 50px; } \
                    QPushButton { color: white; background-color: #45A29E; border: 2px solid #1F2833; font-size: 30px; }\
                    QPushButton:hover { border: 2px solid white; }\
                    QPushButton:disabled { background-color: #0B0C10; }\
                    ");
    GameWindow w;
    w.show();
    return a.exec();
}
