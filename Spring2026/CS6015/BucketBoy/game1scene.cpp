#include "game1scene.h"

game1scene::game1scene() {

    this->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    bucket = new class bucket();
    this->addItem(bucket);
    bucket->setPos(SCREEN_WIDTH / 2 - bucket::PLAYER_HEIGHT / 2, SCREEN_HEIGHT - bucket::PLAYER_HEIGHT - 10); //center-screen, bottom + 10px buffer
    bucket->setFlag(QGraphicsItem::ItemIsFocusable);
    bucket->setFocus();

    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512) .scaledToWidth(910)));

    updateObj = new QObject();
    QTimer *update_timer = new QTimer(updateObj);
    updateObj->connect(update_timer, &QTimer::timeout, this, &game1scene::update);
    update_timer->start(1000/60); //aim for 60 fps

    timer = new QElapsedTimer();
    timer->start();

    score = 0;
    lives = START_LIVES;

    spawnRate = SPAWN_INTERVAL_INIT;
    lastSpawnElapsed = 0;
    lastSpawnRateIncreaseElapsed = 0;
}

void game1scene::update()
{
    float delta = timer->restart() / 1000.0f;

    //Update and check spawn timers
    lastSpawnElapsed += delta;
    lastSpawnRateIncreaseElapsed += delta;
    if(lastSpawnElapsed > spawnRate)
    {
        lastSpawnElapsed = 0;
        class waterdrop* drop = new class waterdrop();
        this->addItem(drop);
        drops.append(drop);
    }
    if(lastSpawnRateIncreaseElapsed > SPAWN_RATE_INCREASE_INTERVAL)
    {
        lastSpawnRateIncreaseElapsed = 0;
        spawnRate *= SPAWN_RATE_INCREASE;
    }

    //Handle drops
    QList<waterdrop*> toRemove;
    for(waterdrop* drop : drops){
        //Movement
        drop->setY(drop->y() + DROP_SPEED * delta);

        //Collision
        if(drop->collidesWithItem(bucket))
        {
            toRemove.append(drop);
            score++;
        }
        //Offscreen
        else if(drop->y() > SCREEN_HEIGHT){
            toRemove.append(drop);
            lives--;
        }
    }

    for(waterdrop* drop : toRemove){
        this->removeItem(drop);
        drops.removeOne(drop);
        delete drop;
    }

    //TODO: update score

    if(lives <= 0)
    {
        //Update text and stop timer
        update_timer->stop();
    }

}
