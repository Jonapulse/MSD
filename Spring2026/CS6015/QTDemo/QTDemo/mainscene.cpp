#include "mainscene.h"
#include "man.h"

mainscene::mainscene() {
    setBackgroundBrush(QPixmap("://images/butterfly.jpg").scaled(300, 300));
    setSceneRect(0,0,300,300);
    man *manObj = new man();
    addItem(manObj);

}
