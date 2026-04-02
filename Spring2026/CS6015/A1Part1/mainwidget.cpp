#include "mainwidget.h"

/**
 * Layout
 * VBox vvv
 * --------------------------------------v GridLayout 4x4
 * QLabel      | QLineEdit      | QSpacer | QLabel  | QSpinBox
 * QLabel      | QLine Edit     | {empty} | {empty} | {empty}
 * QLabel      | QVbox{QRadiox2}| {empty} | {empty} | {empty}
 * QPushButton | {empty}        | {empty} | {empty} | {empty}
 * ------------------------------------------------------
 * QTextEdit
 * ------------------------------------------------------
 * QPushButton
 * ------------------------------------------------------
 * @brief mainWidget::mainWidget
 */
mainWidget::mainWidget() {
    QVBoxLayout *rootLayout = initAndFill();

    //Hook up Signals/Slots
    QObject::connect(refreshPB, &QPushButton::clicked, this, &mainWidget::fillSummary);
    QObject::connect(finishPB, &QPushButton::clicked, this, &mainWidget::clear);

    setLayout(rootLayout);
}

void mainWidget::fillSummary(){
    QString genderStr = "Declined to select";
    if(maleRB->isChecked())
        genderStr = "Male";
    else if(femaleRB->isChecked())
        genderStr = "Female";
    QString summaryStr = "First Name: " + fNameLE->text()
                        + "\nLast Name: " + lNameLE->text()
                        + "\nAge: " + ageSB->text()
                         + "\nGender: " + genderStr;
    summaryDisplayTE->setPlainText(summaryStr);
}

void mainWidget::clear(){
    fNameLE->clear();
    lNameLE->clear();
    ageSB->setValue(0); //Resetting age to default '0' to match startup
    summaryDisplayTE->clear();

    //Remove and re-add autoexclusion to deselect radio buttons
    femaleRB->setAutoExclusive(false);
    maleRB->setAutoExclusive(false);
    femaleRB->setChecked(false);
    maleRB->setChecked(false);
    femaleRB->setAutoExclusive(true);
    maleRB->setAutoExclusive(true);
}

/**
 * Fill main VBox
 * @brief mainWidget::initAndFill
 * @return pointer to main VBoxLayout
 */
QVBoxLayout* mainWidget::initAndFill(){
    //Set up and add Top Grid
    QVBoxLayout *vBoxRoot = new QVBoxLayout();
    QGridLayout *entryGrid = initAndFillGrid();
    summaryDisplayTE = new QTextEdit();
    finishPB = new QPushButton("Finish");
    vBoxRoot->addLayout(entryGrid);

    //Add middle Text Edit
    vBoxRoot->addWidget(summaryDisplayTE);

    //Add displayButton
    vBoxRoot->addWidget(finishPB);

    return vBoxRoot;
}

/**
 * Fill the top grid
 * @brief mainWidget::initAndFillGrid
 * @return poitner to top grid
 */
QGridLayout* mainWidget::initAndFillGrid(){
    QGridLayout* entryGrid = new QGridLayout();
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

    //Put QWidgets in Layouts
    entryGrid->addWidget(fNameL, 0, 0);
    entryGrid->addWidget(fNameLE, 0, 1);
    entryGrid->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
    entryGrid->addWidget(ageL, 0, 3);
    entryGrid->addWidget(ageSB, 0, 4);
    entryGrid->addWidget(lNameL, 1, 0);
    entryGrid->addWidget(lNameLE, 1, 1);
    entryGrid->addWidget(genderL, 2, 0);
    rbVBox->addWidget(maleRB);
    rbVBox->addWidget(femaleRB);
    entryGrid->addLayout(rbVBox, 2, 1);
    entryGrid->addWidget(refreshPB, 3, 0);

    return entryGrid;
}
