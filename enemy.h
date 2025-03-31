#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QTransform>

enum class EAnimState {
    Idle,
    Run, //主动触发
    Attack,//主动触发
    Atked,
};

enum class EDirection {
    Left,
    Right
};

class enemy : public QObject {
    Q_OBJECT

public:
    enemy(QObject *parent = nullptr);
    ~enemy();

    int E_HP;

    // 更新动画
    void EupdateAnimation();
    // 更新位置
    void EupdatePosition();
    // 获取当前图像
    QPixmap EgetCurrentImage();

    // 设置状态
    void EsetState(EAnimState state);
    // 设置方向
    void EsetDirection(EDirection direction);

    // 获取当前状态
    EAnimState EgetState() const;
    // 获取当前方向
    EDirection EgetDirection() const;

    // 获取位置
    int getEX() const;
    int getEY() const;

    QTimer *coolDownTimer;//每隔一段时间进行活动

signals:
    void EanimationUpdated();
    void EatkLaunch();
public:
    EAnimState EcurrentState;
    EDirection EcurrentDirection;

    int Ex, Ey;
    int EvelocityX;
    int EVx = 5;

    // 动画帧计数
    int EcurrentRunFrame;
    int EcurrentAttackFrame;
    int EcurrentAtkedFrame;

    // 图像资源
    QPixmap EidleImage;
    QPixmap ErunImages[56];
    QPixmap EattackImages[54];
    QPixmap EatkedImages[20];
    QPixmap EstiffImage;
    // 当前显示的图像
    QPixmap EcurrentImage;

    // 加载图像资源
    void EloadImages();
    // 镜像图像
    void EmirrorImage();
    //被攻击判定
    void EbeAirAtked();
    void EbeSlashAtked();
    //僵直判定
    QTimer *stiffTimer;
    void Estiff();

};

#endif // ENEMY_H
