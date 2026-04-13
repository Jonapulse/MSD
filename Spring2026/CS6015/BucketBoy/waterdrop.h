#ifndef WATERDROP_H
#define WATERDROP_H

#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

class waterdrop : public QObject, public QGraphicsPixmapItem
{
public:
    waterdrop();
private:
    static constexpr int STAGE_WIDTH = 910;
    void set_random_spawn_point();
};

#endif // WATERDROP_H
