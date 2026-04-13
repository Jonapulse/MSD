#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <QElapsedTimer>
#include <QObject>
#include <QDebug>
#include "bucket.h"
#include "waterdrop.h"


class game1scene : public QGraphicsScene
{
public:
    static constexpr int SCREEN_HEIGHT = 510;
    static constexpr int SCREEN_WIDTH = 908;

    game1scene();


private slots:
    void update(); //Handle game loop (drop creation, drop deletion, win condition, collision)

private:
    QGraphicsPixmapItem* bucket;
    QList<waterdrop*> drops;

    QObject*        updateObj;
    QTimer*         update_timer;
    QElapsedTimer*  timer;  //Used to get 'delta' between update frames

    float spawnRate;
    float lastSpawnElapsed;
    float lastSpawnRateIncreaseElapsed;

    int score;
    int lives;

    static constexpr float DROP_SPEED                   = 200.0f; //pixels/s
    static constexpr float SPAWN_INTERVAL_INIT          = 1.0f; //s
    static constexpr int   START_LIVES                  = 3;
    static constexpr float SPAWN_RATE_INCREASE          = 0.75;
    static constexpr int SPAWN_RATE_INCREASE_INTERVAL   = 10.0f; //s

};

#endif // GAME1SCENE_H
