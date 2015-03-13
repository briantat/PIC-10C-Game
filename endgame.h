#ifndef ENDGAME
#define ENDGAME

#include <QWidget>
#include <QLabel>
#include <QPushButton>

/** @class EndGame
    @brief EndGame class.

    @details This class opens up an window indicating whether you finished a level or failed a level.
*/
class EndGame : public QWidget
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = 0);
    ~EndGame();
    void modifyMessage(const char* newmessage);
    void setGameBoard(QWidget* game_board);

private:
    QLabel* quit_label;
    QPushButton* oka;
    QWidget* board;
};


#endif // ENDGAME

