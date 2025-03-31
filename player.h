#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>

#include "swordair.h"
//玩家状态
enum class AnimState {
    Idle,
    Run,
    Attack,
    Jump,
    Defence,
    Atked,
    Slash
};
//玩家方向
enum class Direction {
    Left,
    Right
};

class Player : public QObject {
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();
    //剑气
    SwordAir *Air;
    // 更新动画
    void updateAnimation();
    // 更新位置
    void updatePosition();
    // 获取当前图像
    QPixmap getCurrentImage();
    // 设置状态
    void setState(AnimState state);
    // 设置方向
    void setDirection(Direction direction);
    // 获取当前状态
    AnimState getState() const;
    // 获取当前方向
    Direction getDirection() const;
    //跳跃轨迹控制
    double jumpTrack();
    // 获取位置
    int getX() const;
    int getY() const;
    //检测状态是否改变，若改变则还原各状态帧序列索引
    bool isStateChanged();
    //记录反击前后位置，用于判定敌人是否被击中
    int slashPreviousX;
    int slashAfterX;

signals:
    void animationUpdated();
    void atkLaunch();//发动攻击
    void slashEffectShow();//显示反击特效
    void slashEffectShowStop();//移除反击特效
    void slashLaunch();//发动反击

public:
    AnimState currentState;//当前状态
    AnimState previousState;//之前状态
    Direction currentDirection;//当前方向

    int x, y;//坐标
    int velocityX, velocityY;//当前速度
    int Vx = 5,Vy = -15;//移动进行时的移动速度
    int HP;//生命值
    bool isJumping;//判定是否在跳跃中
    // 动画帧计数
    int currentRunFrame;
    int currentAttackFrame;
    int currentJumpFrame;
    int currentDefenceFrame;
    int currentAtkedFrame;
    int currentSlashFrame;
    // 图像资源
    QPixmap idleImage;
    QPixmap runImages[36];
    QPixmap attackImages[25];
    QPixmap jumpImages[22];
    QPixmap defenceImages[27];
    QPixmap atkedImages[10];
    QPixmap slashImages[54];
    // 当前显示的图像
    QPixmap currentImage;
    // 加载图像资源
    void loadImages();
    // 镜像图像
    void mirrorImage();
    //被攻击判定
    void beAtked();
    //发出剑气
    void attackWithSwordAir();
};

#endif // PLAYER_H
