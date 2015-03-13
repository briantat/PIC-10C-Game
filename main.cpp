/**
    @mainpage PIC 10C Project "Rescue and Recon"
    @author Brian Tat
    @date March 12, 2015
    @version 1.0
    @brief This is a game for the PIC 10C class. Be sure to have music/sound on when playing the game!
*/

#include "mainwindow.h"
#include "quitwidget.h"
#include "instwidget.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QGridLayout>
#include <random>
#include "gameboard.h"
#include "endgame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Q_INIT_RESOURCE(Images);

    QuitWidget* qwidget = new QuitWidget;
    InstWidget* iwidget = new InstWidget;
    MainWindow* w = new MainWindow;
    GameBoard* b = new GameBoard;
    EndGame* ewidget = new EndGame;

    w->setInstWidget(iwidget);

    w->setQuitWidget(qwidget);
    b->setQuitWidget(qwidget);

    ewidget->setGameBoard(b);
    w->setGameBoard(b);
    b->setMainWindow(w);

    b->setEndGame(ewidget);
    w->show();


    QObject::connect(qwidget->quit_ok, SIGNAL(clicked()), &a, SLOT(quit()));

    return a.exec();
}
