#include "player.h"
#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent),
    currentState(AnimState::Idle),
    previousState(AnimState::Idle),
    currentDirection(Direction::Right),
    x(600),
    y(200),
    velocityX(0),
    velocityY(0),
    isJumping(false),
    currentRunFrame(0),
    currentAttackFrame(0),
    currentJumpFrame(0),
    currentDefenceFrame(0),
    currentAtkedFrame(0),
    Vx(10),
    HP(500)
{
    loadImages();

    Air = new SwordAir(this);
    Air->setParent(this);
}

Player::~Player()
{

}

void Player::loadImages() {
    idleImage.load(":/character/img/character/maincharacter.png");
    for (int i = 0; i < 36; i++) {
        runImages[i].load(QString(":/character/img/character/runFrames/runFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for (int i = 0; i < 25; i++) {
        attackImages[i].load(QString(":/character/img/character/atkFrames/atkFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for (int i = 0; i < 22; i++) {
        jumpImages[i].load(QString(":/character/img/character/jumpFrames/jumpFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for (int i = 0; i < 27; i++) {
        defenceImages[i].load(QString(":/character/img/character/defenceFrames/defenceFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for (int i = 0; i <10; i++)
    {
        atkedImages[i].load(QString(":/character/img/character/atkedFrames/atkedFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for (int i = 0; i <54; i++)
    {
        slashImages[i].load(QString(":/character/img/character/slashFrames/slashFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    // 设置初始图像
    currentImage = idleImage;
}
//更新动画帧索引
void Player::updateAnimation() {
    if(isStateChanged())//检测状态改变进行帧索引还原
    {
        currentAttackFrame = 0;
        currentDefenceFrame = 0;
        currentJumpFrame = 0;
        currentRunFrame = 0;
        currentAtkedFrame = 0;
        currentSlashFrame = 0;
    }
    switch (currentState) {
    case AnimState::Idle:
        currentImage = idleImage;
        break;
    case AnimState::Run:
        currentRunFrame = (currentRunFrame + 1) % 36;
        currentImage = runImages[currentRunFrame];
        break;
    case AnimState::Attack:
        if(currentAttackFrame<23) currentAttackFrame++;
        else
        {
            setState(AnimState::Idle);
            currentAttackFrame = 0;
        }
        if(currentAttackFrame == 14)
        {
            attackWithSwordAir();
        }
        currentImage = attackImages[currentAttackFrame];
        break;
    case AnimState::Jump:
        if(currentJumpFrame<21) currentJumpFrame++;
        else
        {
            setState(AnimState::Idle);
            currentJumpFrame = 0;
        }
        currentImage = jumpImages[currentJumpFrame];
        break;
    case AnimState::Defence:
        if(currentDefenceFrame<26) currentDefenceFrame++;
        else
        {
            setState(AnimState::Idle);
            currentDefenceFrame = 0;
        }
        currentImage = defenceImages[currentDefenceFrame];
        break;
    case AnimState::Atked:
        if(currentAtkedFrame<9) currentAtkedFrame++;
        else
        {
            setState(AnimState::Idle);
            currentAtkedFrame = 0;
        }
        currentImage = atkedImages[currentAtkedFrame];
        break;
    case AnimState::Slash:
        if(currentSlashFrame<53) currentSlashFrame++;
        else
        {
            setState(AnimState::Idle);
            currentSlashFrame = 0;
            emit slashEffectShowStop();
        }
        if(currentSlashFrame == 44)
        {
            emit slashEffectShow();
            if(this->getDirection()==Direction::Left)
            {
                this->x-=1000;
                slashPreviousX = this->getX();
                slashAfterX = slashPreviousX - 1000;
            }
            else
            {
                this->x+=1000;
                slashPreviousX = this->getX();
                slashAfterX = slashPreviousX + 1000;
            }
        }
        currentImage = slashImages[currentSlashFrame];
        break;
    }

    mirrorImage(); //根据方向进行镜像绘制
}
//位置更新
void Player::updatePosition() {
    // 更新位置
    x += velocityX;
    y += jumpTrack();
    // 边界检查
    if (x < 0) x = 0;
    if (x > 1600 - 100) x = 1600 - 100;
    //跳跃边界检查
    if(y > 200) y = 200;
    if(y != 200)
    {
        if(currentState != AnimState::Jump) y=200; //还原高度
    }
}
//镜像绘制
void Player::mirrorImage() {
    if (currentDirection == Direction::Right) {
        currentImage = currentImage.transformed(QTransform().scale(-1, 1));
    }
}
//获取图像
QPixmap Player::getCurrentImage() {
    return currentImage;
}
//设置状态
void Player::setState(AnimState state) {
    switch(state)
    {
    case AnimState::Idle:
        velocityX = 0;
        previousState = currentState;
        currentState = AnimState::Idle;break;
    case AnimState::Run:
        velocityX = (currentDirection == Direction::Right) ? Vx : -Vx;
        previousState = currentState;
        currentState = AnimState::Run;break;
    case AnimState::Jump:
        previousState = currentState;
        currentState = AnimState::Jump;break;
    case AnimState::Defence:
        velocityX = 0;
        previousState = currentState;
        currentState = AnimState::Defence;break;
    case AnimState::Attack:
        velocityX = 0;
        previousState = currentState;
        currentState = AnimState::Attack;break;
    case AnimState::Atked:
        velocityX = 0;
        previousState = currentState;
        currentState = AnimState::Atked;break;
    case AnimState::Slash:
        velocityX = 0;
        previousState = currentState;
        currentState = AnimState::Slash;break;
    }
}
//跳跃轨道
double Player::jumpTrack()
{
    if(currentJumpFrame < 9) return 0;
    else
    {
        return 10*(currentJumpFrame - 15);
    }
}
//设置方向
void Player::setDirection(Direction direction) {
    currentDirection = direction;
}

AnimState Player::getState() const {
    return currentState;
}

Direction Player::getDirection() const {
    return currentDirection;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

bool Player::isStateChanged()
{
    return currentState!=previousState;
}
//被攻击处理
void Player::beAtked()
{
    setState(AnimState::Atked);
    HP -= 50;
}
//发出剑气
void Player::attackWithSwordAir()
{
    if(getDirection() == Direction::Left) Air->setDirection(SwordAir::sDirection::Left);
    else Air->setDirection(SwordAir::sDirection::Right);
    Air->isLauched = true;
    Air->Vx = (Air->nowDirection==SwordAir::sDirection::Right)? 50:-50;
    Air->x = this->getX();
}

