#include "traveling.h"
#include "ui_traveling.h"
#include "QTimer"

Traveling::Traveling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Traveling),
    world(b2Vec2(0.0f, -10.0f))
{
    ui->setupUi(this);

    // Road background
    QLabel *road = new QLabel(this);
    road->setPixmap(QPixmap(":/Resources/road.png").scaled(this->size()));

    // Set road background lower than car sprite
    road->lower();
    road->resize(this->size());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Traveling::updateWorld);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;

    fixtureDef.restitution = 0.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    connect(timer, &QTimer::timeout, this, &Traveling::carEndReached);
}

void Traveling::updateWorld()
{
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 1;
    int32 positionIterations = 1;

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = body->GetPosition();
    ui->car->move(position.x * 100 * 5, CAR_Y);

    float maxSpeed = 2.0f;
    b2Vec2 currentVelocity = body->GetLinearVelocity();

    if (currentVelocity.x < maxSpeed) {
        b2Vec2 xAxis = b2Vec2(1.0f, 0.0f);
        body->ApplyForceToCenter(xAxis, true);
    }
}

void Traveling::carEndReached()
{
    updateWorld();

    // Car reached the end of the screen
    if (ui->car->pos().x() + ui->car->width() > this->width()) {
        disconnect(timer, &QTimer::timeout, this, &Traveling::updateWorld);
        timer->stop();
        emit endOfScreen(true);
    }
}

void Traveling::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    // Reset car start position and timer
    resetStartPosition();
    timer->start(20);
}

void Traveling::resetStartPosition(){
    // Set start position and body's rotation so it would remain unchanged
    b2Vec2 startPosition(0.0f, 4.0f);
    body->SetTransform(startPosition, body->GetAngle());
    ui->car->move(startPosition.x * 100 * 5, CAR_Y);
}

Traveling::~Traveling()
{
    delete ui;
}
