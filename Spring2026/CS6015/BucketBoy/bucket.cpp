#include "bucket.h"

bucket::bucket() {
    setPixmap((QPixmap(":/images/bucket.png")).scaled(PLAYER_HEIGHT, PLAYER_HEIGHT));
}

void bucket::keyPressEvent(QKeyEvent *event){
    float x_mov = 0;
    if(event->key() == (Qt::Key_Right))
        x_mov += 1;
    if(event->key() == (Qt::Key_Left))
        x_mov -= 1;

    this->setPos(this->x() + x_mov * MOV_SPEED, this->y());
}
