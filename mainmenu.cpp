#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->startButton,&QPushButton::clicked,this,&MainMenu::startButtonClicked);
}

void MainMenu::startButtonClicked()
{
    bool clicked = true;
    emit startTheGame(clicked);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resizeEvent(QResizeEvent*)
{
    QPixmap img(":/Resources/menuBG.jpg");
    img = img.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, img);
    this->setPalette(palette);
}
