#include "dialoglogic.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <QTimer>
#include "scene.h"
#include <QPixmap>

DialogLogic::DialogLogic(QObject *parent)
    : QObject{parent}
{
    createScenesMap();
    addBackgroundImages();
    addCharcterImages();
    currScene = "Opening_Monologue";
    currSceneIndex = 0;
    metLee = false;
    metCop = false;
    metMarina = false;
    knowsAboutDr = false;
    knowsAboutGDM = false;
    gaveFinalReport = false;
    end = false;
}

void DialogLogic::createScenesMap()
{
    QFile file(":/Resources/PlayerDialog.txt");
    bool firstLine = true;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line;
        QString currScene = "";
        QTextStream in(&file);
        while(!in.atEnd())
        {
            line = in.readLine();
            if(firstLine)
            {
                currScene = line;
                Scene * s = new Scene(currScene);
                scenes[currScene] = s;
                firstLine = false;
            }
            else if(line == "x"){
                firstLine = true;
            }
            else if(line != ""){
                scenes[currScene]->addLine(line);
            }
        }
    }
}

void DialogLogic::sendInfoToUI(int index)
{
    emit updateDialog(scenes[currScene]->getLine(index));
    emit updateCharacter(scenes[currScene]->getSpeaker(index));
    emit updateCharacterImage(characterImages[scenes[currScene]->getSpeaker(index)]);
    if(scenes[currScene]->hasBackgroundImage())
    {
        emit updateBackgroundImage(scenes[currScene]->getBackgroundImage());
    }
}

void DialogLogic::getNextDialog()
{
    if(currSceneIndex < scenes[currScene]->numOfLines())
    {
        sendInfoToUI(currSceneIndex);
        currSceneIndex++;
    }
    else
    {
        sendSignalToUpdateNotes();
        emit endScene();
    }
}

void DialogLogic::sendSignalToUpdateNotes(){
    if(currScene == "Tutorial"){
        emit showInfo(currScene);
    }
    else if(currScene == "Marina_Start")
    {
        emit showInfo(currScene);
    }
    else if(currScene == "Marina_Pos")
    {
        emit showInfo(currScene);
    }
    else if(currScene == "Cop_Start")
    {
        emit showInfo(currScene);
    }
    else if(currScene == "Cop_Pos")
    {
        emit showInfo(currScene);
    }
    else if(currScene =="Lee_Start")
    {
        emit showInfo(currScene);
    }
}

void DialogLogic::addBackgroundImages()
{
    // Create each pixmap
    QPixmap opening(":/Resources/opening monologue image.png");
    QPixmap fbi(":/Resources/fbi_background.png");
    QPixmap marina(":/Resources/marina_bck2.png");
    QPixmap cop(":/Resources/cop_detective.png");
    QPixmap lee(":/Resources/reporter_background.png");
    QPixmap closeing(":/Resources/closing monologue image.png");
    // Add pixmap to each scene
    scenes["Opening_Monologue"]->addBackgroundImage(opening);
    scenes["Marina_Start"]->addBackgroundImage(marina);
    scenes["Tutorial"]->addBackgroundImage(fbi);
    scenes["Acted_Alone"]->addBackgroundImage(fbi);
    scenes["Conspiracy_NA"]->addBackgroundImage(fbi);
    scenes["Conspiracy_DR"]->addBackgroundImage(fbi);
    scenes["Conspiracy_GDM"]->addBackgroundImage(fbi);
    scenes["Conspiracy_DR_GDM"]->addBackgroundImage(fbi);
    scenes["Cop_Start"]->addBackgroundImage(cop);
    scenes["Lee_Start"]->addBackgroundImage(lee);
    scenes["Closing_Monologue"]->addBackgroundImage(closeing);
}

void DialogLogic::addCharcterImages()
{
    characterImages.insert("President Lyndon Johnson: ", QPixmap(":/Resources/lyndonJohnson telephone.jpg"));
    characterImages.insert("Private Detective: ", QPixmap(":/Resources/detectiveIcon.png"));
    characterImages.insert("FBI Agent: ", QPixmap(":/Resources/fbi-agent-portrait.png"));
    characterImages.insert("Marina Oswald: ", QPixmap(":/Resources/Marina_Oswald_icon.jpg"));
    characterImages.insert("Dallas Officer: ", QPixmap(":/Resources/cop_icon.png"));
    characterImages.insert("Dallas Reporter: ", QPixmap(":/Resources/reporterIcon.png"));
}

void DialogLogic::getNextScene()
{
    if(currScene == "Opening_Monologue"){
        currScene = "President_Johnson_Request";
        sendInfoToUI(0);
        currSceneIndex = 1;
    }
    else if(currScene == "President_Johnson_Request"){
        currScene = "Tutorial";
        sendInfoToUI(0);
        currSceneIndex = 1;
    }
    else if(currScene == "Marina_Start" || currScene == "Cop_Start")
    {
        emit makeDecision("Positve Question", "Negative Question", "Select a Question to Ask");
    }
    else if(metCop && metLee && metMarina && !gaveFinalReport){
        emit updateBackgroundImage(QPixmap(":/Resources/Street film noir.png"));
        emit makeDecision("Lee Acted Alone", "Conspiracy", "Its time to make your final report. What do you think happened?" );
        gaveFinalReport = true;
    }
    else if(gaveFinalReport && !end){
        currScene = "Closing_Monologue";
        sendInfoToUI(0);
        currSceneIndex = 1;
        end = true;
    }
    else if(end){
        emit dialogEnded();
        resetDialog();
        sendInfoToUI(0);
    }
    else{
        emit pickNextInterview(metMarina, metCop, metLee);
    }
}

void DialogLogic::getNextInterview(QString person)
{
    if(person == "marina"){
        currScene = "Marina_Start";
        metMarina = true;
    }
    else if(person == "cop"){
        currScene = "Cop_Start";
        metCop = true;
    }
    else{
        currScene = "Lee_Start";
        metLee = true;
    }
    emit showTraveling();
    sendInfoToUI(0);
    currSceneIndex = 1;
}

void DialogLogic::negativeResponse()
{
    if(currScene == "Marina_Start"){
        currScene = "Marina_Neg";
    }
    else if(currScene == "Cop_Start" && metLee){
        currScene = "Cop_Neg_Aft_Ruby";
    }
    else if(currScene == "Cop_Start"){
        currScene = "Cop_Neg_Bef_Ruby";
    }
    else if(!knowsAboutDr && !knowsAboutGDM){
        currScene = "Conspiracy_NA";
    }
    else if(knowsAboutDr && !knowsAboutGDM){
        currScene = "Conspiracy_DR";
    }
    else if(!knowsAboutDr && knowsAboutGDM){
        currScene = "Conspiracy_GDM";
    }
    else{
        currScene = "Conspiracy_DR_GDM";
    }
    sendInfoToUI(0);
    currSceneIndex = 1;
}

void DialogLogic::positiveResponse()
{
    if(currScene == "Marina_Start"){
        currScene = "Marina_Pos";
        knowsAboutGDM = true;
    }
    else if(currScene == "Cop_Start"){
        currScene = "Cop_Pos";
        knowsAboutDr = true;
    }
    else{
        currScene = "Acted_Alone";
    }
    sendInfoToUI(0);
    currSceneIndex = 1;
}

void DialogLogic::resetDialog() {
    createScenesMap();
    addBackgroundImages();
    currScene = "Opening_Monologue";
    currSceneIndex = 0;
    metLee = false;
    metCop = false;
    metMarina = false;
    knowsAboutDr = false;
    knowsAboutGDM = false;
    gaveFinalReport = false;
    end = false;
}
