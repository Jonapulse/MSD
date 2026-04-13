#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "bucket.h"
#include "waterdrop.h"


class game1scene : public QGraphicsScene
{
public:
    static constexpr int SCREEN_HEIGHT = 510;
    static constexpr int SCREEN_WIDTH = 908;

    game1scene();
    QGraphicsPixmapItem* bucket;
    QGraphicsPixmapItem* drop;

};

#endif // GAME1SCENE_H
