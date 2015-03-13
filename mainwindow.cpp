#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gameboard.h"

/**
    Default constructor for the MainWindow class

    @param parent is the widget in which this widget will be a child of
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Labels for welcome and categories
    welcome = new QLabel("Rescue and Recon!");
    welcome -> setStyleSheet("QLabel {border-style: outset; \
                              border-width: 2px; \
                              border-color: black; border-radius: 10px; \
                              font: bold 20px;\
                              padding: 6px; \
                              background-color: white}");

    difficulty = new QLabel("Difficulty");
    welcome->setAlignment(Qt::AlignCenter);
    difficulty->setAlignment(Qt::AlignCenter);

    difficulty -> setStyleSheet("QLabel {border-style: outset; \
                                            border-width: 2px; \
                                            border-color: black; border-radius: 10px; \
                                            font: bold 15px;\
                                            padding: 6px; \
                                            background-color: white}");

    // PushButtons for the difficulties
    inst = new QPushButton("Instructions");
    L1 = new QPushButton("Level 1");
    L2 = new QPushButton("Level 2");
    L3 = new QPushButton("Level 3");

    QString style = QString("QPushButton {border-style: outset;"
                        "border-width: 2px;"
                        "border-color: black; border-radius: 12px;"
                        "font: bold 12px;"
                        "padding: 6px;"
                        "background-color:white;"
                        "font-family: Times New Roman"
                        "}"

                        "QPushButton:pressed{"
                            "border-color: red;}");


    inst -> setStyleSheet(QString("QPushButton {border-style: outset;"
                          "border-width: 2px;"
                          "border-color: black; border-radius: 12px;"
                          "font: bold 15px;"
                          "padding: 6px;"
                          "background-color:white;"
                          "}"

                          "QPushButton:pressed{"
                              "border-color: red;}"));

    L1 -> setStyleSheet(style);

    L2 -> setStyleSheet(style);

    L3 -> setStyleSheet(style);


    // Layout to make the difficulties line up
    diffs = new QVBoxLayout;
    diffs->addWidget(difficulty);
    //diffs->addWidget(inst);
    diffs->addWidget(L1);
    diffs->addWidget(L2);
    diffs->addWidget(L3);



    // Place the modes and difficulties side-by-side
    two_cols = new QHBoxLayout;
    two_cols->addWidget(inst);
    two_cols->addLayout(diffs);

    // Piece together the welcome message and two columns together
    final_layout = new QVBoxLayout;
    final_layout->addWidget(welcome);
    final_layout->addLayout(two_cols);

    central = new QWidget;
    central->setLayout(final_layout);
    central->setStyleSheet("background-color: green;");

    this->setWindowTitle("Rescue and Recon");
    this->setCentralWidget(central);    
}

/**
    Destructor for the MainWindow class
*/
MainWindow::~MainWindow()
{

}

/**
    When the MainWindow closes, it will show the QuitWidget

    @param e is the QCloseEvent that occurs when the window for the GameBoard is closed.
*/
void MainWindow::closeEvent(QCloseEvent *e) {

    e->ignore();
    qwidget->show();

}

/**
    Sets the QuitWidget.

    @param quit_widget is the MainWindow created in main
*/
void MainWindow::setQuitWidget(QuitWidget* quit_widget) {
    qwidget = quit_widget;
}

/**
    Sets the GameBoard. Needed to set the parameters of the game

    @param game_board is the GameBoard created in main
*/
void MainWindow::setGameBoard(GameBoard* game_board) {
    board = game_board;

    QObject::connect(L1, SIGNAL(clicked()), board, SLOT(updateLevel1()));
    QObject::connect(L2, SIGNAL(clicked()), board, SLOT(updateLevel2()));
    QObject::connect(L3, SIGNAL(clicked()), board, SLOT(updateLevel3()));
}

/**
    Sets the InstWidget. Needed to show the instructions of the game

    @param inst_widget is the InstWidget created in main
*/
void MainWindow::setInstWidget(InstWidget* inst_widget) {
    iwidget = inst_widget;

    QObject::connect(inst, SIGNAL(clicked()), iwidget, SLOT(show()));
}

/**
    Sets the EndGame for a level change needed for GameBoard.

    @param end_game is the EndGame created in main
*/
void MainWindow::setEndGame(EndGame* end_game) {
    ewidget = end_game;
}
