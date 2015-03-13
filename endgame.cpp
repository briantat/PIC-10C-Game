#include "endgame.h"
#include <QHBoxLayout>
#include <QPushButton>

/**
    Default constructor for the EndGame class

    @param parent is the widget in which this widget will be a child of
*/
EndGame::EndGame(QWidget *parent) :
    QWidget(parent)
{

    quit_label = new QLabel("BLAH BLAH BLAH");
    quit_label->setStyleSheet("QLabel {border-style: outset; \
                        border-width: 2px; \
                        border-color: black; border-radius: 10px; \
                        font: bold 12px;\
                        padding: 6px; \
                        background-color: white}");
    quit_label->setWordWrap(true);
    oka = new QPushButton("OK!");

    oka ->setStyleSheet(QString("QPushButton {border-style: outset;"
                                "border-width: 2px;"
                                "border-color: black; border-radius: 12px;"
                                "font: bold 15px;"
                                "padding: 6px;"
                                "background-color:white;"
                                "}"

                                "QPushButton:pressed{"
                                    "border-color: red;}"));

    QVBoxLayout* quit_vlayout = new QVBoxLayout;
    quit_vlayout->addWidget(quit_label);
    quit_vlayout->addWidget(oka);

    this->setStyleSheet("background-color: green;");
    this->setFixedSize(100,120);
    this->setWindowTitle("Rescue and Recon");
    this->setLayout(quit_vlayout);
}

/**
    Destructor for the EndGame class
*/
EndGame::~EndGame()
{ }

/**
    Modifying the message of the quit_label depending on the message.

    @param newmessage is the new message for the quit_label
*/
void EndGame::modifyMessage(const char* newmessage){
    quit_label->setText(newmessage);
}

/**
    Setting the GameBoard for the EndGame. Allows the EndGame PushButtons to hide the EndGame and show the GameBoard

    @param game_board is the QWidget that EndGame needs to connect with in order to hide it.
*/
void EndGame::setGameBoard(QWidget* game_board) {
    board = game_board;
    QObject::connect(oka, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(oka, SIGNAL(clicked()), board, SLOT(show()));
}

