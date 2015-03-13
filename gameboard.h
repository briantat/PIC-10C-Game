#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QMediaPlayer>
#include <QWidget>
#include "quitwidget.h"
#include "mainwindow.h"
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
#include <QPlainTextEdit>
#include "endgame.h"


/** @class GameBoard
    @brief GameBoard class.

    @details This class is where all of the game related code is contained in also including the images and the music for the game.
*/
class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
    void updateWolves();
    void updateLevel1();//int i);
    void updateLevel2();//int i);
    void updateLevel3();//int i);

public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

   void keyPressEvent(QKeyEvent *event);
   void paintEvent(QPaintEvent *e);
   void paintrange(int x, int y);
   void cleanrange(int px, int py);
   void closeEvent(QCloseEvent *e);

   bool retrieveSheep(int x, int y);
   void updateCharacter(int px, int py, int nx, int ny);
   bool isWolf (int x, int y);
   bool isSheep (int x, int y);
   bool isHouse (int x, int y);
   void setQuitWidget(QuitWidget* quit_widget);
   void setMainWindow(MainWindow* main_window);
   void setEndGame(EndGame* end_game);
   void gameOver();

private:

   QPixmap* sheep_image;
   QPixmap* wolf_image;
   QPixmap* character_image;
   QPixmap* house_image;

   QPoint* house_position;
   QPoint* sheep_positions;
   QPoint* character_position;
   QPoint* wolf_positions;
   size_t number_wolf;
   size_t number_sheep;

   // Bottom bar variables
   QWidget* Bottom;
   QLabel** lives;
   QLabel** water;
   int initial_water;
   int mylevel;
   unsigned int lives_remaining;
   QLabel* water_supply;
   unsigned int water_remaining;
   QLabel* sheep_supply;
   unsigned int sheep_remaining;
   QLabel* level_value;
   QHBoxLayout* allwater;
   QHBoxLayout* bottom_bar;
   QHBoxLayout* justhearts;
   QLabel* water_text;
   QLabel* sheep_text;
   QHBoxLayout* allsheep;
   QLabel* level_text;
   QHBoxLayout* alllevel;
   QVBoxLayout* livesandsheep;
   QVBoxLayout* waterandlevel;

   // Board Variables
   QWidget *Board;
   int board_size;
   QLabel** labels;
   QLabel** background;

   QMediaPlayer* music;
   QMediaPlayer* wolf_bite;
   QuitWidget* qwidget;
   MainWindow* mw;
   EndGame* end;
};

#endif // GAMEBOARD_H

