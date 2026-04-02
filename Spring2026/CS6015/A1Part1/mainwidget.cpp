#include "mainwidget.h"

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
mainWidget::mainWidget() {
    //Init layouts
    QVBoxLayout *vBoxRoot = new QVBoxLayout();
    QGridLayout *entryGrid = new QGridLayout();
    QVBoxLayout *rbVBox = new QVBoxLayout();

    //Init QWidgets
    fNameL = new QLabel("First Name");
    fNameLE = new QLineEdit();
    ageL = new QLabel("Age");
    ageSB = new QSpinBox();
    lNameL = new QLabel("Last Name");
    lNameLE = new QLineEdit();
    genderL = new QLabel("Gender");
    genderRBs = new QButtonGroup();
    maleRB = new QRadioButton("male");
    femaleRB = new QRadioButton("female");
    refreshPB = new QPushButton("Refresh");
    nameDisplayTE = new QTextEdit();
    finishPB = new QPushButton("Finish");

    //Hook up Signals/Slots

    //Put QWidgets in Layouts
    //Fill & add top grid
    entryGrid->addWidget(fNameL, 0, 0);
    entryGrid->addWidget(fNameLE, 0, 1);
    entryGrid->addWidget(ageL, 0, 2);
    entryGrid->addWidget(ageSB, 0, 3);
    entryGrid->addWidget(lNameL, 1, 0);
    entryGrid->addWidget(lNameLE, 1, 1);
    entryGrid->addWidget(genderL, 2, 0);
    rbVBox->addWidget(maleRB);
    rbVBox->addWidget(femaleRB);
    entryGrid->addLayout(rbVBox, 2, 1);
    vBoxRoot->addLayout(entryGrid);
    //Add middle Text Edit
    vBoxRoot->addWidget(nameDisplayTE);
    //Add displayButton
    vBoxRoot->addWidget(finishPB);

    setLayout(vBoxRoot);

}
