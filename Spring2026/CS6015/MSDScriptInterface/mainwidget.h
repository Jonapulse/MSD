#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <string>

/**
 * Layout
 * QGridLayout
 * -------------------
 * QLabel  | QTextEdit
 * -------------------
 * {empty} | VBox(QRadioButton x 2)
 * -------------------
 * {empty} | QPushButton
 * -------------------
 * Qlabel  | QTextEdit
 * -------------------
 * {empty} | QPushButton
 * -------------------
 * @brief mainWidget::mainWidget
 */
class mainWidget : public QWidget
{
public:
    mainWidget();

private:
    QLabel *expressionL;
    QTextEdit *expressionTE;
    QButtonGroup *modeRBs;
    QRadioButton *interpRB;
    QRadioButton *pretPrintRB;
    QPushButton *submitPB;
    QLabel *resultL;
    QTextEdit *resultTE;
    QPushButton *resetPB;

    void callMSDScript();
    void reset();

    //Helper function to simplify init
    QGridLayout* initAndFill();
};

#endif // MAINWIDGET_H