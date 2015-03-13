#include "instwidget.h"
#include <QHBoxLayout>
#include <QPlainTextEdit>

/**
    Default constructor for the InstWidget class

    @param parent is the widget in which this widget will be a child of
*/
InstWidget::InstWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(300,320);

    // QPlainTextEdit
    text = new QLabel("Locate all of the sheep in the dark but avoid all wolves. \
You have a limited range of sight.\n\nOnce you leave your house, you have a limited supply of water.\
 Once it hits 0, you will lose a life and be returned home! Replenish your water supply by returning home.\n\nUse the arrows keys to navigate through the darkness..\
 Press the space button with your character on top of the sheep to rescue the sheep! \n\n\
Once you have rescued all the sheep, return home to finish the level."
                      );
    //text -> setReadOnly(true);
    text->setWordWrap(true);
    text->setStyleSheet("QLabel {border-style: outset; \
                        border-width: 2px; \
                        border-color: black; border-radius: 10px; \
                        font: bold 12px;\
                        padding: 6px; \
                        background-color: white}");

    ok = new QPushButton("OK");
    ok-> setStyleSheet("QPushButton {background-color: white; \
                         border-style: outset; \
                         border-width: 2px; \
                         border-color: black; border-radius: 10px; \
                         font: bold 10px;\
                         padding: 6px; }");
    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(text);
    vlayout->addWidget(ok);

    this->setLayout(vlayout);
    this->setStyleSheet("background-color: green;");
   // this->setMaximumWidth(200);
    QObject::connect(ok, SIGNAL(clicked()), this,SLOT(close()));
    this->setWindowTitle("Instructions");

}

/**
    Destructor for the InstWidget class
*/
InstWidget::~InstWidget()
{ }


