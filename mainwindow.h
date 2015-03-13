#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include "quitwidget.h"
#include "instwidget.h"
#include <QRadioButton>
#include "endgame.h"


class GameBoard;

/** @class MainWindow
    @brief MainWindow class.

    @details This class is where options for the game is avaliable, including instructions and level of the game.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

 public slots:

public:
    explicit MainWindow(QWidget *parent = 0);

    void closeEvent(QCloseEvent *e);

    ~MainWindow();

    void setQuitWidget(QuitWidget* quit_widget);
    void setGameBoard(GameBoard* game_board);
    void setInstWidget(InstWidget* inst_widget);
    void setEndGame(EndGame* end_game);

    /**
     *  ewidget is the EndGame Widget
     */
    EndGame* ewidget;

private:
    QuitWidget* qwidget;
    GameBoard* board;
    InstWidget* iwidget;

    QLabel* welcome;
    QLabel* difficulty;

    QPushButton* inst;
    QPushButton* L1;
    QPushButton* L2;
    QPushButton* L3;

    QVBoxLayout* diffs;
    QVBoxLayout* modes;
    QHBoxLayout* two_cols;
    QVBoxLayout* final_layout;
    QWidget* central;

};

#endif // MAINWINDOW_H
