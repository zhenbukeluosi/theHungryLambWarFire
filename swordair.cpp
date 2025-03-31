#include "swordair.h"

SwordAir::SwordAir(QObject *parent)
    : QObject{parent},Vx(30),y(200),isLauched(false),isDamageMade(false)
{
    img.load(":/img/C:/Users/lenovo/Downloads/swordAir-removebg-preview.png");
}

void SwordAir::setDirection(sDirection direction)
{
    nowDirection = direction;
}
//镜像绘制剑气图像
QPixmap SwordAir::getSwordAirImg()
{
    if(nowDirection == sDirection::Right) return img.transformed(QTransform().scale(-1, 1));
    else return img;
}
