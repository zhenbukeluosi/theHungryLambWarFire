#ifndef SLASHEFFECT_H
#define SLASHEFFECT_H

#include <QObject>
#include <QPixmap>

class slashEffect : public QObject
{
    Q_OBJECT
public:
    explicit slashEffect(QObject *parent = nullptr);

    QPixmap slashEffectImg;

signals:
};

#endif // SLASHEFFECT_H
