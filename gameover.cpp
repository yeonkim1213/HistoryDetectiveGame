#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    connect(ui->restartButton,&QPushButton::clicked,this,&GameOver::restartButtonClicked);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::restartButtonClicked()
{
    bool clicked = true;
    emit restartTheGame(clicked);
}

void GameOver::resizeEvent(QResizeEvent*)
{
    // Set background image
    QPixmap image(":/Resources/gameoverBackground.png");
    image = image.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, image);
    this->setPalette(palette);
}
