#ifndef QUITWIDGET_H
#define QUITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

/** @class QuitWidget
    @brief QuitWidget class.

    @details This class opens up an window asking if you are sure about quitting the game.
*/
class QuitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuitWidget(QWidget *parent = 0);
    ~QuitWidget();

    /**
     *  quit_ok is the QPushButton that will quit the whole application
     */
    QPushButton* quit_ok;
private:

    QLabel* quit_label;
    QPushButton* quit_cancel;

};

#endif // QUITWIDGET_H
