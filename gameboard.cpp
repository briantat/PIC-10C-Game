#include "gameboard.h"
#include "ui_gameboard.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

/**
    Default constructor for the GameBoard class

    @param parent is the widget in which this widget will be a child of
*/
GameBoard::GameBoard(QWidget *parent) : QWidget(parent), board_size(19) {
    Bottom = new QWidget;

    bottom_bar = new QHBoxLayout(Bottom);
    justhearts = new QHBoxLayout;

    sheep_image = new QPixmap(":/Images/sheep.jpg");
    character_image = new QPixmap(":/Images/charactersprite.jpg");
    house_image = new QPixmap(":/Images/house.jpg");

    lives_remaining = 3;
    lives = new QLabel*[lives_remaining];

    for(size_t i=0;i<lives_remaining;i++) {
        lives[i] = new QLabel;
        lives[i]->setPixmap(QPixmap(":/Images/heart.jpg"));
        lives[i]->setMinimumSize(15,15);
        lives[i]->setMaximumSize(15,15);
        lives[i]->setScaledContents(true);
        justhearts->addWidget(lives[i]);
    }
    /*
    QString style = QString("QLabel {border-style: outset; \
                            border-width: 2px; \
                            border-color: black; border-radius: 10px; \
                            font: 12px;\
                            padding: 6px; \
                            background-color: white}");
    */

    water_remaining = initial_water;
    water_text = new QLabel("Water Supply:");
    water_supply = new QLabel(QString::number(water_remaining));
    //water_text->setStyleSheet(style);
    //water_supply->setStyleSheet(style);

    allwater = new QHBoxLayout;
    allwater->addWidget(water_text);
    allwater->addWidget(water_supply);

    sheep_remaining = 5;
    sheep_text = new QLabel("Sheep Remaining:");
    sheep_supply = new QLabel(QString::number(sheep_remaining));
    //sheep_text->setStyleSheet(style);
    //sheep_supply->setStyleSheet(style);

    allsheep = new QHBoxLayout;
    allsheep->addWidget(sheep_text);
    allsheep->addWidget(sheep_supply);

    level_text = new QLabel("Level: ");
    level_value = new QLabel(QString::number(1));
    //level_text->setStyleSheet(style);
    //level_value->setStyleSheet(style);

    alllevel = new QHBoxLayout;
    alllevel->addWidget(level_text);
    alllevel->addWidget(level_value);

    livesandsheep = new QVBoxLayout;
    livesandsheep->addLayout(justhearts);
    livesandsheep->addLayout(allsheep);

    waterandlevel = new QVBoxLayout;
    waterandlevel->addLayout(allwater);
    waterandlevel->addLayout(alllevel);

    bottom_bar->addLayout(livesandsheep);
    QSpacerItem* horizontal_space = new QSpacerItem(100,10);
    bottom_bar->addSpacerItem(horizontal_space);
    bottom_bar->addLayout(waterandlevel);

    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    std::uniform_int_distribution<int> distribution(1,board_size);


    for(int i=0;i<board_size;i++) {
        for(int j=0;j<board_size;j++) {
            // Create label and set properties.
            labels[i*board_size+j] = new QLabel;
            labels[i*board_size+j]->setScaledContents(true);
            labels[i*board_size+j]->setMinimumSize(30,30);
            labels[i*board_size+j]->setMaximumSize(30,30);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color: black; color : black; }");
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            // Add label to the layout
            SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }

    character_position = new QPoint((board_size-1)/2,(board_size-1)/2);
    labels[character_position->x()*board_size +character_position->y()]->setPixmap(*character_image);
    labels[character_position->x()*board_size +character_position->y()]->setScaledContents(true);

    house_position = new QPoint((board_size-1)/2,(board_size-1)/2);
    labels[house_position->x()*board_size +house_position->y()]->setPixmap(*house_image);
    labels[house_position->x()*board_size +house_position->y()]->setScaledContents(true);




    //Board->setFixedSize(400,400);
    Board->setFixedSize(600,600);


    // Create a vertical box layout for the two pieces
    QVBoxLayout *piece_together = new QVBoxLayout;

    piece_together->addWidget(Board,0,Qt::AlignCenter);
    piece_together->addWidget(Bottom,0,Qt::AlignCenter);

    this->setLayout(piece_together);

    wolf_image = new QPixmap(":/Images/wolf-6.jpg");

    number_wolf = 4;
    wolf_positions = new QPoint[number_wolf];
/*
    wolf_positions[0].setX(8);
    wolf_positions[0].setY(8);
*/
    wolf_positions[0].setX(-1);
    wolf_positions[0].setY(distribution(generator)%board_size);

    wolf_positions[1].setX(board_size);
    wolf_positions[1].setY(distribution(generator)%board_size);

    wolf_positions[2].setY(-1);
    wolf_positions[2].setX(distribution(generator)%board_size);

    wolf_positions[3].setY(board_size);
    wolf_positions[3].setX(distribution(generator)%board_size);

    number_sheep = 5;
    sheep_positions = new QPoint[number_sheep];


    sheep_positions[0].setX(5);
    sheep_positions[0].setY(distribution(generator)%board_size);

    sheep_positions[1].setX(8);
    sheep_positions[1].setY(distribution(generator)%board_size);

    sheep_positions[2].setY(15);
    sheep_positions[2].setX(distribution(generator)%board_size);

    sheep_positions[3].setY(17);
    sheep_positions[3].setX(distribution(generator)%board_size);

    sheep_positions[4].setY(10);
    sheep_positions[4].setX(10);


/*
    sheep_positions[0].setX(11);
    sheep_positions[0].setY(11);

    sheep_positions[1].setX(12);
    sheep_positions[1].setY(12);

    sheep_positions[2].setY(13);
    sheep_positions[2].setX(13);

    sheep_positions[3].setY(14);
    sheep_positions[3].setX(14);

    sheep_positions[4].setY(10);
    sheep_positions[4].setX(10);
    */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWolves()));
    timer->start(100);

    this->setWindowTitle("Rescue and Recon");

    //play music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/pokemon.mp3"));

    wolf_bite = new QMediaPlayer();
    wolf_bite->setMedia(QUrl("qrc:/music/bite.mp3"));
}

/**
    Destructor for the GameBoard class
*/
GameBoard::~GameBoard() {
    // According to
    delete [] wolf_positions;
    delete [] character_position;
    delete [] sheep_positions;
    delete [] house_position;
}

/**
    Public slot function for updating the GameBoard with the level and the water. Parameters for Level 1.
*/
void GameBoard::updateLevel1(){
    initial_water = 100; mylevel = 1;

    water_remaining = initial_water;
    water_supply->setText(QString::number(water_remaining));
    level_value->setText(QString::number(mylevel));

    QCoreApplication::processEvents();
    repaint();
    show();
}

/**
    Public slot function for updating the GameBoard with the level and the water. Parameters for Level 2.
*/
void GameBoard::updateLevel2(){
    initial_water = 50; mylevel = 2;

    water_remaining = initial_water;
    water_supply->setText(QString::number(water_remaining));
    level_value->setText(QString::number(mylevel));

    QCoreApplication::processEvents();
    repaint();
    show();
}

/**
    Public slot function for updating the GameBoard with the level and the water. Parameters for Level 3.
*/
void GameBoard::updateLevel3(){
    initial_water = 35; mylevel = 3;

    water_remaining = initial_water;
    water_supply->setText(QString::number(water_remaining));
    level_value->setText(QString::number(mylevel));

    QCoreApplication::processEvents();
    repaint();
    show();
}

/**
    Public slot function for updating the wolf positions.
*/
void GameBoard::updateWolves(){
    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);

    for(size_t i=0;i<number_wolf;i++) {
        int px = wolf_positions[i].rx();
        int py = wolf_positions[i].ry();

        if(px>=0 && py >= 0 && px<board_size && py<board_size) {
            labels[py*board_size+px]->clear();
            //resetting the whole board and then putting back what was originally there.
            //labels[py*board_size+px]->setText(QString::number(values[py*board_size+px]));
        }

        int nx = px;
        int ny = py;

        // If it is time to move this ogre, then
        if(p(generator) < 0.1) {

            if(x_or_y(generator) == 0) {
                nx = px + 2*increment(generator)-1;
                if(nx >= -1 && nx <= board_size)
                    wolf_positions[i].setX(nx);
            }
            else {
                ny = py + 2*increment(generator)-1;
                if(ny >= -1 && ny <= board_size)
                    wolf_positions[i].setY(ny);
            }
        }
    }

    QCoreApplication::processEvents();
    repaint();
}

/**
    Painting the image of the x and y coordinate . Will paint and sheep or wolf that is at the (x,y) coordinate.

    @param x is the horizontal coordinate
    @param y is the vertical coordinate
*/
void GameBoard::paintrange(int x, int y){
    for(size_t i=0;i<number_sheep;i++) {
            int px = sheep_positions[i].rx();
            int py = sheep_positions[i].ry();

            if(px == x && py == y) {
                labels[py*board_size+px]->clear();
                labels[py*board_size+px]->setPixmap(*sheep_image);
                labels[py*board_size+px]->setScaledContents(true);
            }
        }
    for(size_t i=0;i<number_wolf;i++) {
        int px = wolf_positions[i].rx();
        int py = wolf_positions[i].ry();

        if(px == x && py == y) {
            labels[py*board_size+px]->setPixmap(*wolf_image);
            labels[py*board_size+px]->setScaledContents(true);
        }
    }
}

/**
    Clean the range of the coordinate. Change the coordinates back to black.

    @param px is the horizontal coordinate
    @param py is the vertical coordinate
*/
void GameBoard::cleanrange(int px, int py){
    // right once
    if((px+1)>=0 && py >= 0 && (px+1)<board_size && py < board_size){
        labels[py*board_size+(px+1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[py*board_size+(px+1)]->clear();
    }

    // left once
    if((px-1)>=0 && py >= 0 && (px-1)<board_size && py < board_size){
        labels[py*board_size+(px-1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[py*board_size+(px-1)]->clear();
    }

    // right twice
    if((px+2)>=0 && py >= 0 && (px+2)<board_size && py < board_size){
        labels[py*board_size+(px+2)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[py*board_size+(px+2)]->clear();
    }

    // left twice
    if((px-2)>=0 && py >= 0 && (px-2)<board_size && py < board_size){
        labels[py*board_size+(px-2)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[py*board_size+(px-2)]->clear();
    }

    //up once
    if(px>=0 && (py+1) >= 0 && px<board_size && (py+1)< board_size){
        labels[(py+1)*board_size+px]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py+1)*board_size+px]->clear();
    }

    // up twice
    if(px>=0 && (py+2) >= 0 && px<board_size && (py+2)< board_size){
        labels[(py+2)*board_size+px]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py+2)*board_size+px]->clear();
    }

    // down once
    if(px>=0 && (py-1) >= 0 && px<board_size && (py-1)< board_size){
        labels[(py-1)*board_size+px]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py-1)*board_size+px]->clear();
    }

    //down twice
    if(px>=0 && (py-2) >= 0 && px<board_size && (py-2)< board_size){
        labels[(py-2)*board_size+px]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py-2)*board_size+px]->clear();
    }

    // left once up once
    if((px-1)>=0 && (py+1) >= 0 && (px-1)<board_size && (py+1) < board_size){
        labels[(py+1)*board_size+(px-1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py+1)*board_size+(px-1)]->clear();
    }

    // right once up once
    if((px+1)>=0 && (py+1) >= 0 && (px+1)<board_size && (py+1) < board_size){
        labels[(py+1)*board_size+(px+1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py+1)*board_size+(px+1)]->clear();
    }

    // left once down once
    if((px-1)>=0 && (py-1) >= 0 && (px-1)<board_size && (py-1) < board_size){
        labels[(py-1)*board_size+(px-1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py-1)*board_size+(px-1)]->clear();
    }
    // right once down once
    if((px+1)>=0 && (py-1) >= 0 && (px+1)<board_size && (py-1) < board_size){
        labels[(py-1)*board_size+(px+1)]->setStyleSheet("QLabel { background-color: black; color : black; }");
        labels[(py-1)*board_size+(px+1)]->clear();
    }
}

/**
    A request to repaint all of the GameBoard

    @param e is the QPaintEvent called when there is repaint or update
*/
void GameBoard::paintEvent(QPaintEvent *e) {
    music->play();

    if(isWolf(character_position->rx(), character_position->ry())){

        if(lives_remaining>0){
        cleanrange(character_position->rx(), character_position->ry());
        character_position->setX(house_position->rx());
        character_position->setY(house_position->ry());
        water_remaining = initial_water;
        water_supply->setText(QString::number(water_remaining));
        } else {
            gameOver();
        }
    }

    int x = character_position->rx();
    int y = character_position->ry();

    labels[y*board_size+x]->setPixmap(*character_image);
    labels[y*board_size+x]->setScaledContents(true);

    // right once
    if((x+1)>=0 && y >= 0 && (x+1)<board_size && y < board_size){
        labels[y*board_size+(x+1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x+1, y);
    }

    // left once
    if((x-1)>=0 && y >= 0 && (x-1)<board_size && y < board_size){
        labels[y*board_size+(x-1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x-1,y);
    }

    // right twice
    if((x+2)>=0 && y >= 0 && (x+2)<board_size && y < board_size){
        labels[y*board_size+(x+2)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x+2,y);
    }

    // left twice
    if((x-2)>=0 && y >= 0 && (x-2)<board_size && y < board_size){
        labels[y*board_size+(x-2)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x-2,y);
    }

    //up once
    if(x>=0 && (y+1) >= 0 && x<board_size && (y+1)< board_size){
        labels[(y+1)*board_size+x]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x,y+1);
    }

    // up twice
    if(x>=0 && (y+2) >= 0 && x<board_size && (y+2)< board_size){
        labels[(y+2)*board_size+x]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x,y+2);
    }

    // down once
    if(x>=0 && (y-1) >= 0 && x<board_size && (y-1)< board_size){
        labels[(y-1)*board_size+x]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x,y-1);
    }

    //down twice
    if(x>=0 && (y-2) >= 0 && x<board_size && (y-2)< board_size){
        labels[(y-2)*board_size+x]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x,y-2);
    }

    // left once up once
    if((x-1)>=0 && (y+1) >= 0 && (x-1)<board_size && (y+1) < board_size){
        labels[(y+1)*board_size+(x-1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x-1,y+1);
    }

    // right once up once
    if((x+1)>=0 && (y+1) >= 0 && (x+1)<board_size && (y+1) < board_size){
        labels[(y+1)*board_size+(x+1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x+1,y+1);
    }

    // left once down once
    if((x-1)>=0 && (y-1) >= 0 && (x-1)<board_size && (y-1) < board_size){
        labels[(y-1)*board_size+(x-1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
        paintrange(x-1,y-1);
    }

    // right once down once
    if((x+1)>=0 && (y-1) >= 0 && (x+1)<board_size && (y-1) < board_size){
       labels[(y-1)*board_size+(x+1)]->setStyleSheet("QLabel { background-color: white; color : black; }");
       paintrange(x+1,y-1);
   }

    int t = house_position->rx();
    int u = house_position->ry();

    labels[u*board_size+t]->setPixmap(*house_image);
    labels[u*board_size+t]->setScaledContents(true);


}

/**
    A function that takes in the key to have an effect on the character

    @param event is the QKeyEvent that is called when a key is pressed.
*/
void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = character_position->rx();
    int y = character_position->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(character_position->rx() != 0){
            updateCharacter(x,y,x-1,y);
        }
        break;

    case Qt::Key_Right:
        if(character_position->rx() != board_size-1){
            updateCharacter(x,y,x+1,y);
        }
        break;
    case Qt::Key_Up:
        if(character_position->ry() != 0){
            updateCharacter(x,y,x,y-1);
        }
        break;
    case Qt::Key_Down:
        if(character_position->ry() != board_size-1){
            updateCharacter(x,y,x,y+1);
        }
        break;

    case Qt::Key_Space:
        retrieveSheep(x,y);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    QCoreApplication::processEvents();
    repaint();
    return;
}

/**
    Returns a true or false statement whether the sheep is rescued

    @param x is the horizontal coordinate
    @param y is the vertical coordinate
    @return true is returned when the sheep is  rescued on (x,y)
    @return false is returned when the sheep is rescued not on (x,y)
*/
bool GameBoard::retrieveSheep(int x, int y){
    if(isSheep(x,y)){
        sheep_remaining--;
        sheep_supply->setText(QString::number(sheep_remaining));
        return(true);
    } else{
        return(false);
    }
}

/**
    Tests whether the wolf is at the position (x,y). Since the character is being tested, the character will lose a life and there is also a sound effect

    @param x is the horizontal coordinate
    @param y is the vertical coordinate
    @return true is returned when the wolf is on (x,y)
    @return false is returned when the wolf is not on (x,y)
*/
bool GameBoard::isWolf(int x, int y) {
    for(size_t i=0;i<number_wolf;i++) {
        int px = wolf_positions[i].rx();
        int py = wolf_positions[i].ry();
        if(x == px && y == py && lives_remaining > 0) {
            lives[lives_remaining-1]->hide();
            lives_remaining--;
            if(wolf_bite->state() == QMediaPlayer::PlayingState)
                wolf_bite->setPosition(1);
            else if (wolf_bite->state() != QMediaPlayer::PlayingState)
                wolf_bite->play();
            return true;
        }
    }
    return false;
}

/**
    Returns a true or false statement whether the sheep is at (x,y) position

    @param x is the horizontal coordinate
    @param y is the vertical coordinate
    @return true is returned when the sheep is on (x,y)
    @return false is returned when the sheep is not on (x,y)
*/
bool GameBoard::isSheep(int x, int y) {
    for(size_t i=0;i<number_sheep;i++) {
        int px = sheep_positions[i].rx();
        int py = sheep_positions[i].ry();
        if(x == px && y == py) {
            sheep_positions[i].setX(50);
            return true;
        }
    }
    return false;
}

/**
    Returns a true or false statement whether the house is at (x,y) position

    @param x is the horizontal coordinate
    @param y is the vertical coordinate
    @return true is returned when the house is on (x,y)
    @return false is returned when the house is not on (x,y)
*/
bool GameBoard::isHouse(int x, int y) {
    int px = house_position->rx();
    int py = house_position->ry();
    if(x == px && y == py) {
        water_remaining = initial_water;
        if(sheep_remaining == 0){
            gameOver();
        }
        return true;
    }
    return false;
}

/**
    Updates the character's position

    @param px is the old horizontal coordinate
    @param py is the old vertical coordinate
    @param nx is the new horizontal coordinate
    @param ny is the new vertical coordinate
*/
void GameBoard::updateCharacter(int px, int py, int nx, int ny) {
    labels[py*board_size+px]->clear();
    cleanrange(px, py);

    character_position->setX(nx);
    character_position->setY(ny);

    if(water_remaining != 0){
        water_remaining = water_remaining-1;
        water_supply->setText(QString::number(water_remaining));
    }
    if(isHouse(character_position->rx(),character_position->ry())){
        water_supply->setText(QString::number(water_remaining));
    }

    if(lives_remaining > 0 && water_remaining == 0) {
        character_position->setX(house_position->rx());
        character_position->setY(house_position->ry());
        water_remaining = initial_water;
        water_supply->setText(QString::number(water_remaining));
        lives[lives_remaining-1]->hide();
        lives_remaining--;
    }

    if(lives_remaining == 0 || (lives_remaining == 1 && water_remaining ==0)){
        gameOver();
    }
}

/**
    Game Over state of the game. Will update the level and reset the positions of sheep and wolves.
*/
void GameBoard::gameOver(){
    if(sheep_remaining == 0 & mylevel == 3){
        end->modifyMessage("Congratulations!\n That's it!");
    }
    if(sheep_remaining == 0 & mylevel < 3){
        end->modifyMessage("Congratulations!\n Next level!");
        if(mylevel ==2){
            updateLevel3();
        }
        if(mylevel == 1){
            updateLevel2();
        }
    }

    if(lives_remaining == 0){
        end->modifyMessage("Game Over! You lost all of your lives!");
    }
    hide();
    music->pause();
    end->show();

    lives_remaining = 3;
    for(size_t i=0;i<lives_remaining;i++) {
        lives[i]->show();
    }
    sheep_remaining = 5;
    sheep_supply->setText(QString::number(sheep_remaining));

    int px = character_position->rx();
    int py = character_position->ry();

    labels[py*board_size+px]->clear();
    cleanrange(px,py);

    character_position->setX(house_position->rx());
    character_position->setY(house_position->ry());

    water_remaining = initial_water;
    water_supply->setText(QString::number(water_remaining));


    std::uniform_int_distribution<int> distribution(1,board_size);

    sheep_positions[0].setX(5);
    sheep_positions[0].setY(distribution(generator)%board_size);

    sheep_positions[1].setX(8);
    sheep_positions[1].setY(distribution(generator)%board_size);

    sheep_positions[2].setY(15);
    sheep_positions[2].setX(distribution(generator)%board_size);

    sheep_positions[3].setY(17);
    sheep_positions[3].setX(distribution(generator)%board_size);

    sheep_positions[4].setY(10);
    sheep_positions[4].setX(10);

    wolf_positions[0].setX(-1);
    wolf_positions[0].setY(distribution(generator)%board_size);

    wolf_positions[1].setX(board_size);
    wolf_positions[1].setY(distribution(generator)%board_size);

    wolf_positions[2].setY(-1);
    wolf_positions[2].setX(distribution(generator)%board_size);

    wolf_positions[3].setY(board_size);
    wolf_positions[3].setX(distribution(generator)%board_size);
}

/**
    Sets the quitwidget.

    @param quit_widget is the QuitWidget created in main
*/
void GameBoard::setQuitWidget(QuitWidget* quit_widget) {
    qwidget = quit_widget;
}

/**
    Sets the MainWindow.

    @param main_window is the MainWindow created in main
*/
void GameBoard::setMainWindow(MainWindow* main_window) {
    mw = main_window;
}

/**
    Sets the EndGame for a level change.

    @param end_game is the EndGame created in main
*/
 void GameBoard::setEndGame(EndGame* end_game){
     end = end_game;

 }

 /**
     When the GameBoard closes, it will reset the parameters of the game

     @param e is the QCloseEvent that occurs when the window for the GameBoard is closed.
 */
 void GameBoard::closeEvent(QCloseEvent *e) {
     music->pause();

     if(sheep_remaining >0) {

         for(size_t i=0;i<number_sheep;i++) {
                 int px = sheep_positions[i].rx();
                 int py = sheep_positions[i].ry();
                 labels[py*board_size+px]->clear();
        }
    }

     lives_remaining = 3;
     for(size_t i=0;i<lives_remaining;i++) {
         lives[i]->show();
     }

     int px = character_position->rx();
     int py = character_position->ry();

     labels[py*board_size+px]->clear();
     cleanrange(px,py);

     character_position->setX(house_position->rx());
     character_position->setY(house_position->ry());

     water_remaining = initial_water;
     water_supply->setText(QString::number(water_remaining));

     sheep_remaining = 5;
     sheep_supply->setText(QString::number(sheep_remaining));


     std::uniform_int_distribution<int> distribution(1,board_size);

     sheep_positions[0].setX(5);
     sheep_positions[0].setY(distribution(generator)%board_size);

     sheep_positions[1].setX(8);
     sheep_positions[1].setY(distribution(generator)%board_size);

     sheep_positions[2].setY(15);
     sheep_positions[2].setX(distribution(generator)%board_size);

     sheep_positions[3].setY(17);
     sheep_positions[3].setX(distribution(generator)%board_size);

     sheep_positions[4].setY(10);
     sheep_positions[4].setX(10);

     wolf_positions[0].setX(-1);
     wolf_positions[0].setY(distribution(generator)%board_size);

     wolf_positions[1].setX(board_size);
     wolf_positions[1].setY(distribution(generator)%board_size);

     wolf_positions[2].setY(-1);
     wolf_positions[2].setX(distribution(generator)%board_size);

     wolf_positions[3].setY(board_size);
     wolf_positions[3].setX(distribution(generator)%board_size);

 }
