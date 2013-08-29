#ifndef STUPIDWALLGUN_H
#define STUPIDWALLGUN_H
#include "stalker.h"
#include <QGraphicsItem>

class Stupidwallgun: public Stalker{
    public:
        Stupidwallgun();
        ~Stupidwallgun();
        char getShotdir();  //return bulletshooting direction
        void setShotdir(char a);    //set shooting direction
    protected:
        void advance(int step);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
        int shotdir;
};

#endif // STUPIDWALLGUN_H
