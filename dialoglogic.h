#ifndef DIALOGLOGIC_H
#define DIALOGLOGIC_H

#include <QObject>
#include <QMap>
#include "scene.h"
#include <QPixmap>

///@brief model class to contain all logic nessicary for the dialog ui to function correctly
class DialogLogic : public QObject
{
    Q_OBJECT

public:
    explicit DialogLogic(QObject *parent = nullptr);

public slots:
    ///@brief method to get all dialog from a given scene
    void getNextDialog();
    ///@brief method to determine which scene to play next
    void getNextScene();
    ///@brief method to interview the person the user has selected
    /// @param person - next person to interview
    void getNextInterview(QString);
    ///@brief method to detrmine dialog based on a negative response
    void negativeResponse();
    ///@brief method to determine dialog based on a positive resonse
    void positiveResponse();
    ///@brief resets dialog to inital state
    void resetDialog();

signals:
    ///@brief signal to dialog ui to update character dialog label
    /// @param dialog - text to display
    void updateDialog(QString);
    ///@brief signal to update character name label
    void updateCharacter(QString);
    ///@brief signal to dialog showing who is left to interview
    void pickNextInterview(bool, bool, bool);
    ///@brief signal that all the dialog in a given scene has been given
    void endScene();
    ///@brief signal that the user has a decision to make
    void makeDecision(QString, QString, QString);
    ///@brief signal that the game of over
    void endGame();
    ///@brief signal to show information after an encounter
    void showInfo(QString);
    ///@brief signal to send background image to ui
    void updateBackgroundImage(QPixmap);
    ///@brief singal to emit character image to ui
    void updateCharacterImage(QPixmap);
    ///@brief signal to emit when we want to travel.
    void showTraveling();
    ///@brief signal to send when dialog ends
    void dialogEnded();

private:
    ///@brief map of scene objects which hold player dialog, character names, and images
    QMap<QString, Scene*> scenes;
    ///@brief index's character images by character name
    QMap<QString, QPixmap> characterImages;
    ///@brief key indicating the current scene
    QString currScene;
    ///@brief current dialog in scene
    int currSceneIndex;
    ///@brief indicates whether a the user has interviews marina
    bool metMarina;
    ///@brief indicates whether the user has interviewed the cop
    bool metCop;
    ///@brief indicates whether the user has interviewed lee
    bool metLee;
    ///@brief indicates if the user has learned about dr crenshaw
    bool knowsAboutDr;
    ///@brief indicates if the user has learned about george de morinshildt
    bool knowsAboutGDM;
    ///@brief indicates if the final report has been given
    bool gaveFinalReport;
    ///@brief method to read in each scene with all its dialog
    void createScenesMap();
    ///@brief method to updtate current line from a character
    void sendNextDialog(int);
    ///@brief sends scene info to dialog ui
    void sendInfoToUI(int);
    ///@brief method to send a signal to update player notes
    void sendSignalToUpdateNotes();
    ///@brief method to add background images to each scene
    void addBackgroundImages();
    ///@brief method to add character images for each line
    void addCharcterImages();
    ///@brief indicates game is over
    bool end;
};

#endif // DIALOGLOGIC_H
