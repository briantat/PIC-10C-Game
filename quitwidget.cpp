#include "quitwidget.h"
#include "ui_quitwidget.h"
#include <QHBoxLayout>

/**
    Default constructor for the QuitWidget class

    @param parent is the widget in which this widget will be a child of
*/
QuitWidget::QuitWidget(QWidget *parent) :
    QWidget(parent)
{

    quit_label = new QLabel("Are you sure?");
    quit_cancel = new QPushButton("Cancel");
    quit_ok = new QPushButton("OK");

    QHBoxLayout* quit_hlayout = new QHBoxLayout;
    quit_hlayout->addWidget(quit_cancel);
    quit_hlayout->addWidget(quit_ok);

    QVBoxLayout* quit_vlayout = new QVBoxLayout;
    quit_vlayout->addWidget(quit_label);
    quit_vlayout->addLayout(quit_hlayout);

    this->setLayout(quit_vlayout);

    QObject::connect(quit_cancel, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(quit_ok, SIGNAL(clicked()), this,SLOT(close()));
  //  QObject::connect(quit_ok, SIGNAL(clicked()), this,SLOT());
  //  make your update so that when the game is closed, it will restart.
    this->setWindowTitle("Quit");

}

/**
    Destructor for the QuitWidget class
*/
QuitWidget::~QuitWidget()
{ }

