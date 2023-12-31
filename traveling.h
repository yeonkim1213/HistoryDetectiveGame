#ifndef TRAVELING_H
#define TRAVELING_H

#include <QMainWindow>
#include <Box2D/Box2D.h>

namespace Ui {
///@brief Ui to display car traveling scene using Box2D
class Traveling;
}

class Traveling : public QMainWindow
{
    Q_OBJECT

public:
    explicit Traveling(QWidget *parent = nullptr);
    ~Traveling();
    ///@brief Resets start position of the car from MainWindow
    void resetStartPosition();

protected:
    ///@brief Override showEvent to custom QTimer
    void showEvent(QShowEvent *event) override;

signals:
    ///@brief Signal when car has reached the end of the screen
    /// @param bool - true if car has reached the end of the screeen
    void endOfScreen(bool);

private slots:
    ///@brief Slot to update the world - car movement
    void updateWorld();
    ///@brief Slot to handle when car reached the end
    void carEndReached();

private:
    Ui::Traveling *ui;
    b2World world;
    b2Body* body;
    QTimer* timer;
    int const CAR_Y = 675;
};

#endif // TRAVELING_H
