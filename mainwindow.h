#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialoglogic.h"
#include "traveling.h"
#include "gameover.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainMenu;
class Dialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DialogLogic &, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    ///@brief Show dialog and hide main menu
    /// @param bool - true to show dialog
    void showDialog(bool);
    ///@brief Show traveling and hide dialog
    void showTraveling();
    ///@brief Show traveling again and hide dialog
    void showDialogAfterTraveling();
    ///@brief Show game over and close dialog and traveling
    void showGameOver();
    ///@brief Show main menu and close game over
    void showMainMenu();

private:
    Ui::MainWindow *ui;
    MainMenu *mainMenu;
    Dialog *dialog;
    GameOver *gameOver;
    Traveling *traveling;
};
#endif // MAINWINDOW_H
