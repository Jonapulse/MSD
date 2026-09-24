#ifndef BUCKET_H
#define BUCKET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>

class bucket : public QObject, public QGraphicsPixmapItem
{
public:
    static constexpr int PLAYER_HEIGHT = 150;
    static constexpr int SCREEN_WIDTH = 908;
    bucket();
    void keyPressEvent(QKeyEvent *event);
private:
    static constexpr float MOV_SPEED = 25;
};

#endif // BUCKET_H
