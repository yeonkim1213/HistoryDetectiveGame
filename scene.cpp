#include "scene.h"

Scene::Scene(QString name, QObject *parent)
    : QObject{parent}
{
    this->name = name;
    hasBackground = false;
}

void Scene::addLine(QString line)
{
    QStringList list = line.split(" ");
    QString characterName;
    // Extracts character name from a line leaveing only dialog left
    while(true)
    {
        characterName += list[0] + " ";
        if(list[0].endsWith(":")){
            list.removeFirst();
            break;
        }
        list.removeFirst();
    }
    this->speakingOrder.push_back(characterName);
    this->lines.push_back(list.join(" "));
}

void Scene::addFact(QString fact)
{
    facts.push_back(fact);
}

void Scene::addBackgroundImage(QPixmap image)
{
    backgroundImage = image;
    hasBackground = true;
}

QString Scene::getLine(int index)
{
    if(index < lines.count())
    {
        return lines[index];
    }
    else
    {
        return "";
    }
}

QString Scene::getSpeaker(int index)
{
    if(index < speakingOrder.count()){
        return speakingOrder[index];
    }
    else{
        return "";
    }
}

bool Scene::hasBackgroundImage()
{
    return hasBackground;
}

QPixmap Scene::getBackgroundImage()
{
    return backgroundImage;
}

int Scene::numOfLines()
{
    return lines.count();
}

int Scene::numOfFacts()
{
    return facts.count();
}
