#ifndef BUCKET_H
#define BUCKET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>

class bucket : public QObject, public QGraphicsPixmapItem
{
public:
    static constexpr int PLAYER_HEIGHT = 150;
    bucket();
    void keyPressEvent(QKeyEvent *event);
private:
    static constexpr float MOV_SPEED = 5;
};

#endif // BUCKET_H
