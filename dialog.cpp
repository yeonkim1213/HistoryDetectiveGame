#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(DialogLogic & logic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->negativeDialog->hide();
    ui->positiveDialog->hide();
    ui->interviewCop->hide();
    ui->interviewLee->hide();
    ui->interviewMarina->hide();
    ui->speakerImage->hide();
    ui->dialogDisplay->setWordWrap(true);
    ui->characterName->setWordWrap(true);
    ui->dialogDisplay->hide();
    ui->characterName->hide();
    ui->dialogFrame->hide();
    ui->interviewNotes->setReadOnly(true);
    ui->interviewNotes->viewport()->setCursor(Qt::ArrowCursor);
    ui->interviewNotes->setContentsMargins(20,20,20,20);
    ui->interviewNotes->hide();
    ui->signalUpdate->hide();
    ui->interviewNotes->setText("Case Notes:\n");
    ui->infoLabel->setAlignment(Qt::AlignHCenter);
    ui->infoLabel->setWordWrap(true);
    ui->caseInfo->setWordWrap(true);
    ui->caseFrame->setStyleSheet("color: white;""background-color: gray;");
    QPixmap image(":/Resources/opening monologue image.png");
    image = image.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, image);
    this->setPalette(palette);
    ui->infoLabel->setText("When your ready to solve the crime of the century go on ahead and press that there next button");
    connect(ui->nextButton, &QPushButton::clicked, &logic, &DialogLogic::getNextDialog);
    connect(ui->nextButton, &QPushButton::clicked, ui->caseInfo, &QLabel::hide);

    connect(&logic, &DialogLogic::dialogEnded, this, &Dialog::onDialogEnded);

    connect(&logic, &DialogLogic::updateDialog, ui->infoLabel, &QLabel::hide);
    connect(&logic, &DialogLogic::updateDialog, ui->positiveDialog, &QPushButton::hide);
    connect(&logic, &DialogLogic::updateDialog, ui->negativeDialog, &QPushButton::hide);
    connect(&logic, &DialogLogic::updateDialog, ui->dialogDisplay, &QLabel::show);
    connect(&logic, &DialogLogic::updateDialog, ui->dialogFrame, &QLabel::show);
    connect(&logic, &DialogLogic::updateDialog, ui->speakerImage, &QLabel::show);
    connect(&logic, &DialogLogic::updateDialog, ui->characterName, &QLabel::show);
    connect(&logic, &DialogLogic::updateDialog, ui->dialogDisplay, &QLabel::setText);
    connect(&logic, &DialogLogic::updateDialog, ui->nextButton, &QPushButton::show);
    connect(&logic, &DialogLogic::updateCharacter, ui->characterName, &QLabel::setText);
    connect(&logic, &DialogLogic::endScene, &logic, &DialogLogic::getNextScene);
    connect(&logic, &DialogLogic::pickNextInterview, this, &Dialog::setUpInterview);
    // Select to interview cop
    connect(ui->interviewCop, &QPushButton::clicked, this, [&logic](){logic.getNextInterview("cop");});
    // Hide interview buttons when cop is selected
    connect(ui->interviewCop, &QPushButton::clicked, ui->interviewCop, &QPushButton::hide);
    connect(ui->interviewCop, &QPushButton::clicked, ui->interviewMarina, &QPushButton::hide);
    connect(ui->interviewCop, &QPushButton::clicked, ui->interviewLee, &QPushButton::hide);
    connect(ui->interviewCop, &QPushButton::clicked, ui->infoLabel, &QPushButton::hide);
    connect(ui->interviewCop, &QPushButton::clicked, ui->dialogDisplay, &QPushButton::show);
    connect(ui->interviewCop, &QPushButton::clicked, ui->characterName, &QPushButton::show);
    connect(ui->interviewCop, &QPushButton::clicked, ui->dialogFrame, &QPushButton::show);
    // Select to inerview marina
    connect(ui->interviewMarina, &QPushButton::clicked, this, [&logic](){logic.getNextInterview("marina");});
    // Hide interview buttons when marina is selected
    connect(ui->interviewMarina, &QPushButton::clicked, ui->interviewCop, &QPushButton::hide);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->interviewMarina, &QPushButton::hide);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->interviewLee, &QPushButton::hide);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->infoLabel, &QPushButton::hide);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->dialogDisplay, &QPushButton::show);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->characterName, &QPushButton::show);
    connect(ui->interviewMarina, &QPushButton::clicked, ui->dialogFrame, &QPushButton::show);
    // Select to interview lee
    connect(ui->interviewLee, &QPushButton::clicked, this, [&logic](){logic.getNextInterview("lee");});
    // Hide interview buttons when lee is selected
    connect(ui->interviewLee, &QPushButton::clicked, ui->interviewCop, &QPushButton::hide);
    connect(ui->interviewLee, &QPushButton::clicked, ui->interviewMarina, &QPushButton::hide);
    connect(ui->interviewLee, &QPushButton::clicked, ui->interviewLee, &QPushButton::hide);
    connect(ui->interviewLee, &QPushButton::clicked, ui->infoLabel, &QPushButton::hide);
    connect(ui->interviewLee, &QPushButton::clicked, ui->dialogDisplay, &QPushButton::show);
    connect(ui->interviewLee, &QPushButton::clicked, ui->characterName, &QPushButton::show);
    connect(ui->interviewLee, &QPushButton::clicked, ui->dialogFrame, &QPushButton::show);
    // Show buttons to make a decision
    connect(&logic, &DialogLogic::makeDecision, this, &Dialog::setUpDecision);
    connect(ui->negativeDialog, &QPushButton::clicked, &logic, &DialogLogic::negativeResponse);
    connect(ui->positiveDialog, &QPushButton::clicked, &logic, &DialogLogic::positiveResponse);
    // Send to game over screen
    connect(&logic, &DialogLogic::endGame, this, &Dialog::gameOverScreen);

    connect(&logic, &DialogLogic::showInfo,this,&Dialog::showInfoOnNotes);
    //Goes to slot to update background image
    connect(&logic, &DialogLogic::updateBackgroundImage, this, &Dialog::updateBackgroundImage);
    connect(&logic, &DialogLogic::updateCharacterImage, this, &Dialog::updateCharacterImage);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onDialogEnded() {
    emit gameOverScreen();
}

void Dialog::setUpInterview(bool metMarina, bool metCop, bool metLee)
{
    this->ui->infoLabel->show();
    this->ui->dialogDisplay->hide();
    this->ui->speakerImage->hide();
    this->ui->characterName->hide();
    this->ui->dialogFrame->hide();
    this->ui->nextButton->hide();
    this->ui->infoLabel->setText("Select Next Person to Interview");
    if(!metMarina){
        this->ui->interviewMarina->show();
    }
    if(!metCop){
        this->ui->interviewCop->show();
    }
    if(!metLee){
        this->ui->interviewLee->show();
    }
}

void Dialog::setUpDecision(QString pos, QString neg, QString prompt)
{
    this->ui->infoLabel->show();
    this->ui->nextButton->hide();
    this->ui->dialogDisplay->hide();
    this->ui->speakerImage->hide();
    this->ui->characterName->hide();
    this->ui->dialogFrame->hide();
    this->ui->positiveDialog->show();
    this->ui->negativeDialog->show();
    ui->negativeDialog->setText(neg);
    ui->positiveDialog->setText(pos);
    ui->infoLabel->setText(prompt);
}

void Dialog::on_briefcase_clicked()
{
    if(!notes)
    {
        notes = true;
        ui->interviewNotes->show();
        ui->signalUpdate->hide();
    }
    else if(notes)
    {
        notes = false;
        ui->interviewNotes->hide();
    }
}

void Dialog::showInfoOnNotes(QString sceen){
    if(sceen == "Tutorial")
    {
        ui->interviewNotes->setText("Lee Harvey Oswald \n"
                                    "Age: 24 \n"
                                    "Former Marine Married to Marina Oswald, met in the Soviet Union \n"
                                    "2 Children \n ");
        ui->signalUpdate->show();
    }
    else if(sceen == "Marina_Start")
    {
        QString currText = ui->interviewNotes->toPlainText();
        ui->interviewNotes->setText(currText +
                                    "\n"
                                    "Marina Oswald:\n"
                                    "-Oswald defected to the soviet union where he met his wife Marina\n"
                                    "-Once their first child was born Lee and Marina returned to the United States\n"
                                    "-Lee was critical of capitalists but had no direct hatred of JFK\n");
        ui->signalUpdate->show();
    }
    else if(sceen == "Marina_Pos")
    {
        QString currText = ui->interviewNotes->toPlainText();
        ui->interviewNotes->setText(currText +
                                    "[Additional information]:\n"
                                    "-Lee didn't trust many people. He was mostly a loner\n"
                                    "-George De Mohrenschildt a Russian émigré seemed to take an interest in Lee."
                                    "He helped the family settle back in the US\n"
                                    "-De Mohrenschildt knew the family of Jackie Kennedy (JFK's Wife)\n");
        ui->signalUpdate->show();
    }
    else if(sceen == "Cop_Start")
    {
        QString currText = ui->interviewNotes->toPlainText();
        ui->interviewNotes->setText(currText +
                                    "\n"
                                    "Dallas Officer:\n"
                                    "-Oswald shot at JFK three times from the Texas School Book Depository Building, "
                                    "where he was working at the time.\n"
                                    "-Two of the three shots struck JFK.\n"
                                    "-Oswald was found in a movie theater where he shot officer J.D. Tippit\n"
                                    "-The rifle used was linked to a mail-order purchase that Oswald had made, "
                                    "and there is also photographic evidence to prove that he owned it.\n");
        ui->signalUpdate->show();
    }
    else if(sceen == "Cop_Pos")
    {
        QString currText = ui->interviewNotes->toPlainText();
        ui->interviewNotes->setText(currText +
                                    "[Additional information]:\n"
                                    "-Dr. Charles Crenshaw, one of the doctors who attended to Kennedy after the shooting, "
                                    "claims that the wounds indicated that there were shots from the back, from Lee Harvey Oswald "
                                    "as well as from the front from an unknown gunman.\n");
        ui->signalUpdate->show();
    }
    else if(sceen == "Lee_Start")
    {
        QString currText = ui->interviewNotes->toPlainText();
        ui->interviewNotes->setText(currText +
                                    "\n"
                                    "Jack Ruby:\n"
                                    "-Jack Ruby a Dallas nightclub owner shot Lee Harvey Oswalt on live TV "
                                    "in the Dallas Police Headquarters\n");
        ui->signalUpdate->show();
    }
}

void Dialog::updateBackgroundImage(QPixmap image)
{
    image = image.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, image);
    this->setPalette(palette);
}

void Dialog::updateCharacterImage(QPixmap image)
{
    image = image.scaled(ui->speakerImage->size(), Qt::IgnoreAspectRatio);
    ui->speakerImage->setPixmap(image);
}
