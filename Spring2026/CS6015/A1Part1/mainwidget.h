#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

/**
 * Layout
 * VBox vvv
 * --------------------------------------v GridLayout 4x4
 * QLabel      | QLineEdit           | QLabel  | QSpinBox
 * QLabel      | QLine Edit          | {empty} | {empty}
 * QLabel      | QVbox (QRadioButton)| {empty} | {empty}
 *                     (QRadioButton)
 * QPushButton | {empty}             | {empty} | {empty}
 * ------------------------------------------------------
 * QTextEdit
 * ------------------------------------------------------
 * QPushButton
 * ------------------------------------------------------
 * @brief mainWidget::mainWidget
 */
class mainWidget : public QWidget
{
public:
    mainWidget();

private:
    QLabel *fNameL;
    QLineEdit *fNameLE;
    QLabel *ageL;
    QSpinBox *ageSB;
    QLabel *lNameL;
    QLineEdit *lNameLE;
    QLabel *genderL;
    QButtonGroup *genderRBs;
    QRadioButton *maleRB;
    QRadioButton *femaleRB;
    QPushButton *refreshPB;
    QTextEdit *summaryDisplayTE;
    QPushButton *finishPB;

    void fillSummary();
    void clear();

    //Helper functions to simplify init
    QVBoxLayout* initAndFill();
    QGridLayout* initAndFillGrid();
};

#endif // MAINWIDGET_H
