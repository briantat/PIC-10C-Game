#ifndef INSTWIDGET
#define INSTWIDGET

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>


/** @class InstWidget
    @brief InstWidget class.

    @details This class is where the instructions widget shows up or not. Allows you to view the instructions for gameplay.
*/
class InstWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InstWidget(QWidget *parent = 0);
    ~InstWidget();

    /**
     *  ok is the QPushButton that allows you to close the window
     */
    QPushButton* ok;
private:
    QLabel* text;
    //QPlainTextEdit* text;

};

#endif // INSTWIDGET

