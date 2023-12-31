#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "dialog.h"

MainWindow::MainWindow(DialogLogic & dialogLogic, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainMenu = new MainMenu;
    dialog = new Dialog(dialogLogic);
    traveling = new Traveling();
    gameOver = new GameOver;
    mainMenu->show();

    connect(mainMenu,&MainMenu::startTheGame,this,&MainWindow::showDialog);
    connect(dialog, &Dialog::gameOverScreen, this, &MainWindow::showGameOver);
    connect(&dialogLogic, &DialogLogic::showTraveling, this, &MainWindow::showTraveling);
    connect(gameOver,&GameOver::restartTheGame,this,&MainWindow::showMainMenu);
    connect(traveling, &Traveling::endOfScreen, this, &MainWindow::showDialogAfterTraveling);
}

void MainWindow::showDialog(bool showed){
    if(showed)
    {
        mainMenu->hide();
        dialog->show();
    }
}

void MainWindow::showGameOver(){
    dialog->close();
    traveling->close();
    gameOver->show();
}

void MainWindow::showTraveling(){
    dialog->hide();
    traveling->show();
}

void MainWindow::showDialogAfterTraveling(){
    traveling->hide();
    dialog->show();
}

void MainWindow::showMainMenu(){
    gameOver->close();
    mainMenu->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainMenu;
    delete dialog;
    delete traveling;
}
