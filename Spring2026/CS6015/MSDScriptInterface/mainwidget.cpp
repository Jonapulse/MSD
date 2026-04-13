#include "mainwidget.h"
#include "parse.hpp"

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
mainWidget::mainWidget() {
    QGridLayout *rootLayout = initAndFill();

    //Hook up Signals/Slots
    QObject::connect(submitPB, &QPushButton::clicked, this, &mainWidget::callMSDScript);
    QObject::connect(resetPB, &QPushButton::clicked, this, &mainWidget::reset);

    setLayout(rootLayout);
}

/**
 * It is assumed interp will be selected by default
 * @brief mainWidget::callMSDScript
 */
void mainWidget::callMSDScript(){
    std::string str_to_be_parsed = expressionTE->toPlainText().toStdString();
    std::string output = "";
    try{
        std::shared_ptr<Expr> expr = parse_str(str_to_be_parsed);
        if(interpRB->isChecked()){
            output = expr->interp(Env::empty)->to_string();
        } else
        {
            output = expr->to_pretty_string();
        }
    }
    catch(std::runtime_error e){
        output = "Error:\n";
        output += e.what();
    }
    resultTE->setText(QString::fromStdString(output));
}

void mainWidget::reset(){
    expressionTE->clear();
    resultTE->clear();
    interpRB->setChecked(true);
}

/**
 * Fill main VBox
 * @brief mainWidget::initAndFill
 * @return pointer to main VBoxLayout
 */
QGridLayout* mainWidget::initAndFill(){
    QGridLayout *gridRoot = new QGridLayout();
    QVBoxLayout *modeRBVBox = new QVBoxLayout();

    //Init QWidgets
    expressionL = new QLabel("Expression:");
    expressionTE = new QTextEdit();
    modeRBs = new QButtonGroup();
    interpRB = new QRadioButton("Interp");
    pretPrintRB = new QRadioButton("Pretty Print");
    modeRBs->addButton(interpRB);
    modeRBs->addButton(pretPrintRB);
    modeRBVBox->addWidget(interpRB);
    modeRBVBox->addWidget(pretPrintRB);
    submitPB = new QPushButton("Submit");
    resultL = new QLabel("Result:");
    resultTE = new QTextEdit();
    resetPB = new QPushButton("Reset");

    //Add to grid
    gridRoot->addWidget(expressionL, 0, 0);
    gridRoot->addWidget(expressionTE, 0, 1);
    gridRoot->addLayout(modeRBVBox, 1, 1);
    gridRoot->addWidget(submitPB, 2, 1);
    gridRoot->addWidget(resultL, 3, 0);
    gridRoot->addWidget(resultTE, 3, 1);
    gridRoot->addWidget(resetPB, 4, 1);

    return gridRoot;
}