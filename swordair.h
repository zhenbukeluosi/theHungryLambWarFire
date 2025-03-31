#ifndef SWORDAIR_H
#define SWORDAIR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class SwordAir : public QObject
{
    Q_OBJECT
public:
    explicit SwordAir(QObject *parent = nullptr);

    QPixmap img;

    int Vx;

    int x;

    int y;
    enum class sDirection
    {
        Left,
        Right
    };

    sDirection nowDirection;
    void setDirection(sDirection direction);
    void updatePosition();

    bool isLauched;

    bool isDamageMade;

    QPixmap getSwordAirImg();

signals:
};

#endif // SWORDAIR_H
