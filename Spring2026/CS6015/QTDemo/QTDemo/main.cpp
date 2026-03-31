#include <QApplication>
#include <QPushButton>
#include "mainwidget.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    mainWidget *window = new mainWidget();
    window->show();
    return app.exec();
}
