#include <QGraphicsView>
#include <QApplication>
#include "game1scene.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);

    game1scene *scene1 = new game1scene();
    QGraphicsView *mainview = new QGraphicsView();
    mainview->setScene(scene1);
    mainview->setFixedSize(scene1->SCREEN_WIDTH, scene1->SCREEN_HEIGHT);
    mainview->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    mainview->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    mainview->show();

    return app.exec();
}