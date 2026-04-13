#include "waterdrop.h"

waterdrop::waterdrop() {
    setPixmap((QPixmap(":/images/water.gif")).scaled(30,30));
    set_random_spawn_point();
}

void waterdrop::set_random_spawn_point()
{
    this->setPos(rand() % STAGE_WIDTH, 0);
}