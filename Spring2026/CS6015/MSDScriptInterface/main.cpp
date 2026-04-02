#include <QApplication>
#include "mainwidget.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    mainWidget* mW = new mainWidget();
    mW->show();
    return app.exec();
}