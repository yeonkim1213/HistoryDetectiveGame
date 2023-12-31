#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>
#include <QResizeEvent>

namespace Ui {
///@brief Ui to display gameover screen
class GameOver;
}

class GameOver : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    ~GameOver();
    ///@brief Handle window resizing
    void resizeEvent(QResizeEvent*);

private slots:
    ///@brief Slot to handle restart button click event - direct to main menu
    void restartButtonClicked();

signals:
    ///@brief Send signal when the games needs to be restarted
    /// @param bool - true to restart the game and direct to the main menu
    void restartTheGame(bool);

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
