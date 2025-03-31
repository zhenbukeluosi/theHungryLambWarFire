#include "enemy.h"

enemy::enemy(QObject *parent)
    : QObject{parent},
    EcurrentState(EAnimState::Idle),
    EcurrentDirection(EDirection::Left),
    Ex(1000),
    Ey(200),
    EvelocityX(5),
    EcurrentRunFrame(0),
    EcurrentAttackFrame(0),
    EcurrentAtkedFrame(0),
    E_HP(3000)
{
    coolDownTimer = new QTimer(this);
    coolDownTimer->setInterval(2000);
    coolDownTimer->setSingleShot(true);

    stiffTimer = new QTimer(this);
    stiffTimer->setSingleShot(true);
    stiffTimer->setInterval(54*1000/30);

    EloadImages();
}

enemy::~enemy()
{

}

void enemy::EloadImages()
{
    EidleImage.load(":/enemy/img/enemy/enemyImg.png");
    //load其他IMAGE
    for(int i = 0;i < 56;i++)
    {
        ErunImages[i].load(QString(":/enemy/img/enemy/enemyRunFrames/enemyRunFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for(int i = 0;i < 54;i++)
    {
        EattackImages[i].load(QString(":/enemy/img/enemy/enemyAtkFrames/enemyAtkFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    for(int i = 0;i < 20;i++)
    {
        EatkedImages[i].load(QString(":/enemy/img/enemy/enemyAtkedFrames/enemyAtkedFrame_%1%2.png").arg((i + 1) / 10).arg((i + 1) % 10));
    }
    EstiffImage.load(":/enemy/img/enemy/enemyStiff.png");
    EcurrentImage = EidleImage;
}
// 镜像图像
void enemy::EmirrorImage()
{
    if(EcurrentDirection == EDirection::Right) EcurrentImage = EcurrentImage.transformed(QTransform().scale(-1,1));
}
//被攻击判定
void enemy::EbeAirAtked()
{
    EsetState(EAnimState::Atked);
    EcurrentAtkedFrame = 0;
    E_HP -= 50;
}
//盾反反击判定
void enemy::EbeSlashAtked()
{
    EsetState(EAnimState::Atked);
    EcurrentAtkedFrame = 0;
    E_HP -= 100;
    Estiff();
}

int enemy::getEX()const
{
    return Ex;
}
int enemy::getEY()const
{
    return Ey;
}
//更新动画帧
void  enemy::EupdateAnimation()
{
    if(stiffTimer->isActive())
    {
        EcurrentImage = EstiffImage; //处于僵直状态，返回僵直图像
    }
    else
    {
        switch(EcurrentState)
        {
        case EAnimState::Idle:
            EcurrentImage = EidleImage;break;
        case EAnimState::Run:
            if(EcurrentRunFrame<55)
            {
                EcurrentImage = ErunImages[EcurrentRunFrame];
                EcurrentRunFrame++;
            }
            else
            {
                EsetState(EAnimState::Idle);
                EcurrentImage = EidleImage;
                EcurrentRunFrame = 0;
            }
            break;
        case EAnimState::Attack:
            if(EcurrentAttackFrame<53)
            {
                EcurrentAttackFrame++;
                EcurrentImage = EattackImages[EcurrentAttackFrame];
            }
            else
            {
                EsetState(EAnimState::Idle);
                EcurrentImage = EidleImage;
                EcurrentAttackFrame = 0;
            }
            break;
        case EAnimState::Atked:
            if(EcurrentAtkedFrame<19)
            {
                EcurrentImage = EatkedImages[EcurrentAtkedFrame];
                EcurrentAtkedFrame++;
            }
            else
            {
                EsetState(EAnimState::Idle);
                EcurrentImage = EidleImage;
                EcurrentAtkedFrame = 0;
            }
            break;
        }
    }


    EmirrorImage();
}
// 更新位置
void enemy::EupdatePosition()
{
    Ex += EvelocityX;
    //边界检查
    if (Ex < 0) Ex = 0;
    if (Ex > 1600 - 400) Ex = 1600 - 400;
}
// 获取当前图像
QPixmap enemy::EgetCurrentImage()
{
    return EcurrentImage;
}

// 设置状态
void enemy::EsetState(EAnimState state)
{
    switch(state)
    {
    case EAnimState::Idle:
        EvelocityX = 0;
        coolDownTimer->start();
        EcurrentState = EAnimState::Idle;break;
    case EAnimState::Run:
        EvelocityX = (EcurrentDirection == EDirection::Right) ? EVx : -EVx;
        EcurrentState = EAnimState::Run;break;
    case EAnimState::Attack:
        EvelocityX = 0;
        EcurrentState = EAnimState::Attack;break;
    case EAnimState::Atked:
        EvelocityX = 0;
        EcurrentState = EAnimState::Atked;
        //被攻击后将其他状态动画帧还原至第一帧，防止动画播出不完整
        EcurrentRunFrame = 0;
        EcurrentAttackFrame = 0;
        break;
    }
}
// 设置方向
void  enemy::EsetDirection(EDirection direction)
{
    EcurrentDirection = direction;
}

// 获取当前状态
EAnimState  enemy::EgetState() const
{
    return EcurrentState;
}
// 获取当前方向
EDirection  enemy::EgetDirection() const
{
    return EcurrentDirection;
}
//设置僵直时长
void enemy::Estiff()
{
    stiffTimer->start();
}
