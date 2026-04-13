#include "game1scene.h"

game1scene::game1scene() {

    this->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    bucket = new class bucket();
    this->addItem(bucket);
    bucket->setPos(SCREEN_WIDTH / 2 - bucket::PLAYER_HEIGHT / 2, SCREEN_HEIGHT - bucket::PLAYER_HEIGHT / 2 - 10); //center-screen, bottom + 10px buffer
    bucket->setFlag(QGraphicsItem::ItemIsFocusable);
    bucket->setFocus();

    QGraphicsPixmapItem* drop = new class waterdrop();
    this->addItem(drop);

    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512) .scaledToWidth(910)));
}
