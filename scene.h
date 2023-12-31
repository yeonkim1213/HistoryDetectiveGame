#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QSet>
#include <QPixmap>

///@brief Object to store information about each scene, including lines, facts, and speakers
class Scene : public QObject
{
    Q_OBJECT

public:
    explicit Scene(QString, QObject *parent = nullptr);
    ///@brief method to add a line to the scene
    void addLine(QString);
    ///@brief method to add a fact to a scene
    void addFact(QString);
    ///@brief method to add a background image to scene
    void addBackgroundImage(QPixmap);
    ///@brief method to get a line at a given index
    QString getLine(int);
    ///@brief method to get a speaker at a givne index
    QString getSpeaker(int);
    ///@brief indicates whether this scene has a background image
    bool hasBackgroundImage();
    ///@brief method to retrive a background image
    QPixmap getBackgroundImage();
    ///@brief method to get total number of lines in a scene
    int numOfLines();
    ///@brief method to get total number of facts in a scene
    int numOfFacts();

private:
    ///@brief vector containing each line in a scene
    QVector<QString> lines;
    ///@brief vector corresponding to the order each speaker alernates in a given scene
    QVector<QString> speakingOrder;
    ///@brief vector contating each fact givne in a scene
    QVector<QString> facts;
    ///@brief the name of the scene
    QString name;
    ///@brief background image of scene
    QPixmap backgroundImage;
    ///@brief indicates if scene has a background image
    bool hasBackground;
};

#endif // SCENE_H
