#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include "dialoglogic.h"

namespace Ui {
///@brief ui to display scene and dialog of Detective Adventure
class Dialog;
}

class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dialog(DialogLogic &, QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void onDialogEnded();

signals:
    ///@brief signals to main window that the game is over
    void gameOverScreen();

private slots:
    ///@brief method to set up the ability for the user to select who to interview
    /// @param metMarina - true if user has interviewed Marina
    /// @param metCop - true if user has interviewed the cop
    /// @param metLee - true if user has interviewed lee
    void setUpInterview(bool, bool, bool);
    ///@brief method to set up ablilty for the user to make a decisin
    /// @param pos - text for positive button
    /// @param neg - text for negative button
    /// @param prompt - text to prompt user
    void setUpDecision(QString, QString, QString);
    ///@brief method to detect if the briefcase button is clicked
    void on_briefcase_clicked();
    ///@brief method to show the information that the player have been gathering
    void showInfoOnNotes(QString);
    ///@brief method to update background image on ui
    void updateBackgroundImage(QPixmap);
    ///@breif method to update character imagge on ui
    void updateCharacterImage(QPixmap);

private:
    Ui::Dialog *ui;
    bool notes = false;
};

#endif // DIALOG_H
