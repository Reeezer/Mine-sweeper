#include "gameview.h"

GameView::GameView(QWidget *parent, int size)
    : QWidget(parent), _size(size)
{
    resize(parent->width(), parent->height());

    srand(time(NULL));

    _nbBombsLabel = new QLabel(this);
    _nbBombsLabel->setFont(QFont("GROBOLD"));

    QLabel *flag = new QLabel(this);
    flag->setPixmap(QPixmap(":/res/flagTitle.png"));

    QHBoxLayout *informationLayout = new QHBoxLayout();
    informationLayout->addStretch();
    informationLayout->addWidget(flag);
    informationLayout->addWidget(_nbBombsLabel);
    informationLayout->addStretch();

    _mapGridLayout = new QGridLayout();
    _mapGridLayout->setSpacing(0);
    _mapGridLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addLayout(_mapGridLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(informationLayout);
    mainLayout->addLayout(contentLayout);
    setLayout(mainLayout);

    _buttonList = new QList<Button *>();

    initialize();
}

GameView::~GameView()
{}

void GameView::updateDisplay()
{
    _nbBombsLabel->setText(": " + QString::asprintf("%d", _nbBombs));
}

void GameView::initialize()
{
    _nbBombs = qPow(_size, 2) / 8;
    updateDisplay();

    int buttonSize = (width() > height()) ? (width() / (_size + 3)) : (height() / (_size + 3));

    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            Button *newButton = new Button(this, i, j);
            newButton->setFixedSize(buttonSize, buttonSize);
            _buttonList->append(newButton);
            _mapGridLayout->addWidget(newButton, i, j);
            QObject::connect(newButton, &Button::rightClick, this, &GameView::decreaseBombs);
            QObject::connect(newButton, &Button::leftClick, this, &GameView::checkFlag);
            QObject::connect(newButton, &Button::gameOver, this, &GameView::gameOver);
            QObject::connect(newButton, &Button::empty, this, &GameView::floodFill);
        }
    }

    fillBombs();
}

void GameView::floodFill()
{
    Button *button = qobject_cast<Button *>(QObject::sender());
    int i = button->getX();
    int j = button->getY();

    if ((i - 1) * _size + j - 1 >= 0 && j - 1 >= 0 && _buttonList->at((i - 1) * _size + j - 1)->isEnabled())
        _buttonList->at((i - 1) * _size + j - 1)->leftClicked();
    if ((i - 1) * _size + j >= 0 && _buttonList->at((i - 1) * _size + j)->isEnabled())
        _buttonList->at((i - 1) * _size + j)->leftClicked();
    if ((i - 1) * _size + j + 1 >= 0 && j + 1 < _size && _buttonList->at((i - 1) * _size + j + 1)->isEnabled())
        _buttonList->at((i - 1) * _size + j + 1)->leftClicked();

    if (i * _size + j - 1 >= 0 && j - 1 >= 0 && _buttonList->at(i * _size + j - 1)->isEnabled())
        _buttonList->at(i * _size + j - 1)->leftClicked();
    if (i * _size + j + 1 < _size * _size && j + 1 < _size && _buttonList->at(i * _size + j + 1)->isEnabled())
        _buttonList->at(i * _size + j + 1)->leftClicked();

    if ((i + 1) * _size + j - 1 < _size && j - 1 >= 0 && _buttonList->at((i + 1) * _size + j - 1)->isEnabled())
        _buttonList->at((i + 1) * _size + j - 1)->leftClicked();
    if ((i + 1) * _size + j < _size * _size && _buttonList->at((i + 1) * _size + j)->isEnabled())
        _buttonList->at((i + 1) * _size + j)->leftClicked();
    if ((i + 1) * _size + j + 1 < _size * _size && j + 1 < _size && _buttonList->at((i + 1) * _size + j + 1)->isEnabled())
        _buttonList->at((i + 1) * _size + j + 1)->leftClicked();

}

void GameView::fillBombs()
{
    for (int i = 0; i < _nbBombs; i++)
    {
        int x = -1;
        int y = -1;

        //Fill in bombs
        do
        {
            x = rand() % _size;
            y = rand() % _size;
        } while (_buttonList->at(x * _size + y)->getBomb() == true);
        _buttonList->at(x * _size + y)->setBomb();

        //Increase the number of bombs for every box next to the bombs
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                if (x + dx >= 0 && x + dx < _size && y + dy >= 0 && y + dy < _size && !_buttonList->at((x + dx) * _size + y + dy)->getBomb())
                    _buttonList->at((x + dx) * _size + y + dy)->increaseNbBomb();
    }
}

void GameView::gameOver()
{    
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            Button *button = _buttonList->at(i * _size + j);
            button->displayText();
            button->setEnabled(false);
        }
    }

    QTimer::singleShot(5000, this, &GameView::displaySplashScreen);
}

void GameView::decreaseBombs()
{
    Button *button = qobject_cast<Button *>(QObject::sender());
    if (button->getFlag())
        _nbBombs--;
    else
        _nbBombs++;

    updateDisplay();

    if (_nbBombs == 0)
        gameOver();
}

void GameView::checkFlag()
{
    Button *button = qobject_cast<Button *>(QObject::sender());
    if (button->getFlag()) { // If left click on a flagged button we must increase the number of bombs because it wasn't one
        _nbBombs++;
        updateDisplay();
    }
}
