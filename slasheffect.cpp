#include "slasheffect.h"

slashEffect::slashEffect(QObject *parent)
    : QObject{parent}
{
    slashEffectImg.load(":/img/img/slashEffect.png");
}
