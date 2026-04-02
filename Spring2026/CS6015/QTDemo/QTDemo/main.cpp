#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPushButton>
#include "mainwidget.h"
#include "mainscene.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // create a scene
    // QGraphicsScene *mainscene = new QGraphicsScene();
    // // create an image item
    // QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem();
    // // add the item to the scene
    // imageItem->setPixmap(QPixmap("://images/butterfly.jpg").scaled(200, 200)); //huh, not working. ".webp?" or a syntax error?
    // create a view
    // mainscene->addItem(imageItem);

    mainscene *mainscene = new class mainscene();


    // add the scene to the view
    QGraphicsView *mainView = new QGraphicsView();
    // show the view
    mainView->setScene(mainscene);

    mainView->show();
  //  mainWidget *window = new mainWidget();
   // window->show();
    return app.exec();
}
