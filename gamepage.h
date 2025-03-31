#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QRect>
#include <QTransform>
#include <QPixmap>

#include "player.h"
#include "enemy.h"
#include "swordair.h"
#include "config.h"
#include "slasheffect.h"

namespace Ui
{
class GamePage;
}
class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();
    void airClean();

private:
    Ui::GamePage *ui;
    Player *liang;
    enemy *diren;
    slashEffect *effect;

    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *playerItem;
    QGraphicsPixmapItem *airItem;
    QGraphicsPixmapItem *enemyItem;
    QGraphicsPixmapItem *electricityEffectItem;
    QGraphicsPixmapItem *liangHP;
    QGraphicsPixmapItem *enemyHP;

    QRect swordAirRect;
    QRect liangRect;
    QRect enemyRect;

    // 按键状态
    bool keyAPressed = false;
    bool keyDPressed = false;
    bool keyJPressed = false;
    bool keyKPressed = false;
    bool keyLPressed = false;

    QTimer *gameTimer;
    QTimer *gameCount;

    int randon;//随机数决定敌人动向

    void doesPlayerAttcked();
    void doesEnemyAirAttacked();
    void doesEnemySlashAttacked();

    void paintSlashEffect();
    void removeSlashEffect();

    void gameWin();
    void gameLose();


signals:
    void enemyAirAttacked();
    void enemySlashAttacked();
    void characterAttacked();

    void playerHPzero();
    void enemyHPzero();

    void theGameIsWin();
    void theGameIsLose();
};

#endif // GAMEPAGE_H
