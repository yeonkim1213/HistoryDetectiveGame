#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QEvent>
#include <QHoverEvent>

namespace Ui {
///@brief ui to display main menu of the game
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    ///@brief Handle window resizing
    void resizeEvent(QResizeEvent*);

private slots:
    ///@brief Slot to handle when start button is clicked - move to dialog
    void startButtonClicked();

signals:
    ///@brief Signal when the game is started
    /// @param bool - true when the game should be started
    void startTheGame(bool);

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
