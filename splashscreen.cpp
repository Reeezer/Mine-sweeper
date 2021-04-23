#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *easyButton = new QPushButton(this);
    QPushButton *mediumButton = new QPushButton(this);
    QPushButton *hardButton = new QPushButton(this);
    easyButton->setFixedSize(160, 80);
    mediumButton->setFixedSize(160, 80);
    hardButton->setFixedSize(160, 80);
    easyButton->setIcon(QIcon(":/res/1star.png"));
    mediumButton->setIcon(QIcon(":/res/2star.png"));
    hardButton->setIcon(QIcon(":/res/3star.png"));
    easyButton->setIconSize(QSize(120, 60));
    mediumButton->setIconSize(QSize(120, 60));
    hardButton->setIconSize(QSize(120, 60));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(easyButton);
    buttonLayout->addWidget(mediumButton);
    buttonLayout->addWidget(hardButton);

    QLabel *title = new QLabel("Demineur", this);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("GROBOLD"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(title);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    QObject::connect(easyButton, &QPushButton::clicked, this, &SplashScreen::easy);
    QObject::connect(mediumButton, &QPushButton::clicked, this, &SplashScreen::medium);
    QObject::connect(hardButton, &QPushButton::clicked, this, &SplashScreen::hard);
}

SplashScreen::~SplashScreen()
{}

