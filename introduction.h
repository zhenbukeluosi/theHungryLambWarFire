#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QDialog>
#include <QPixmap>
#include <QFont>

#include "config.h"

namespace Ui {
class Introduction;
}

class Introduction : public QDialog
{
    Q_OBJECT

public:
    explicit Introduction(QWidget *parent = nullptr);
    ~Introduction();

    QPixmap bg;

private:
    Ui::Introduction *ui;
};

#endif // INTRODUCTION_H
