#include "waterdrop.h"

waterdrop::waterdrop() {
    setPixmap((QPixmap(":/images/water.gif")).scaled(30,30));
    QTimer *timer_drop = new QTimer(this);
    // connect(timer_drop, &QTimer::timeout, this, &waterdrop::set_random_spawn_point);
    // timer_drop->start(10);
    set_random_spawn_point();
}

void waterdrop::set_random_spawn_point()
{
    this->setPos(rand() % STAGE_WIDTH, 0);
}


