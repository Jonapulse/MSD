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

    float move_x = this->x() + x_mov * MOV_SPEED;
    if(move_x < 0)
        move_x = 0;
    else if(move_x + PLAYER_HEIGHT > SCREEN_WIDTH)
        move_x = SCREEN_WIDTH - PLAYER_HEIGHT;

    this->setPos(move_x, this->y());
}
