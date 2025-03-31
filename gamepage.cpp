#include "gamepage.h"
#include "ui_gamepage.h"

#include <QDebug>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::GamePage)
{
    ui->setupUi(this);
    this->setFixedSize(1600, 900);
    this->setFocusPolicy(Qt::StrongFocus);

    // 初始化玩家
    liang = new Player(this);
    diren = new enemy(this);
    //反击特效
    effect = new slashEffect(this);
    // 初始化场景和视图
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1600, 900);
    // 添加背景
    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(GAME_BG_PATH));
    scene->addItem(bg);
    // 添加玩家
    playerItem = scene->addPixmap(liang->getCurrentImage());
    playerItem->setPos(liang->getX(), liang->getY());
    //添加剑气
    airItem = scene->addPixmap(liang->Air->img);
    airItem->setPos(liang->getX(),liang->Air->y);
    //添加敌人
    enemyItem = scene->addPixmap(diren->EgetCurrentImage());
    enemyItem->setPos(diren->getEX(),diren->getEY());
    //添加血条
    liangHP = scene->addPixmap(QPixmap(HP_PATH));
    enemyHP = scene->addPixmap(QPixmap(HP_PATH));
    //添加反击特效
    electricityEffectItem = scene->addPixmap(effect->slashEffectImg);
    scene->removeItem(electricityEffectItem);//先移除，触发后再添加
    //设置视图
    view = new QGraphicsView(scene, this);
    view->setFixedSize(1600, 900);
    view->setSceneRect(0, 0, 1600, 900);
    view->show();
    // 游戏更新计时器
    gameTimer = new QTimer(this);
    //游戏倒计时
    gameCount = new QTimer(this);
    //处理动画更新以及状态更新
    connect(gameTimer, &QTimer::timeout, this, &GamePage::updateGame);
    connect(gameTimer,&QTimer::timeout,liang,&Player::updateAnimation);
    connect(gameTimer,&QTimer::timeout,this,&GamePage::airClean);
    connect(gameTimer,&QTimer::timeout,liang,&Player::updatePosition);
    connect(gameTimer,&QTimer::timeout,diren,&enemy::EupdateAnimation);
    connect(gameTimer,&QTimer::timeout,diren,&enemy::EupdatePosition);
    //连接被攻击判定
    connect(liang,&Player::atkLaunch,this,&GamePage::doesEnemyAirAttacked);
    connect(liang,&Player::slashLaunch,this,&GamePage::doesEnemySlashAttacked);
    connect(diren,&enemy::EatkLaunch,this,&GamePage::doesPlayerAttcked);
    //判定成功进行受击处理
    connect(this,&GamePage::enemyAirAttacked,diren,&enemy::EbeAirAtked);
    connect(this,&GamePage::enemySlashAttacked,diren,&enemy::EbeSlashAtked);
    connect(this,&GamePage::characterAttacked,liang,&Player::beAtked);
    //绘制反击特效
    connect(liang,&Player::slashEffectShow,this,&GamePage::paintSlashEffect);
    connect(liang,&Player::slashEffectShowStop,this,&GamePage::removeSlashEffect);
    //图层管理
    playerItem->setZValue(100);
    airItem->setZValue(80);
    electricityEffectItem->setZValue(60);
    enemyItem->setZValue(40);
    bg->setZValue(20);
    liangHP->setZValue(120);
    enemyHP->setZValue(120);
  
    gameTimer->start(1000/30); //30 fps

    gameCount->start(1800000);//游戏倒计时三分钟
    //游戏胜负判定条件
    connect(gameCount,&QTimer::timeout,this,&GamePage::gameLose);
    connect(this,&GamePage::playerHPzero,this,&GamePage::gameLose);
    connect(this,&GamePage::enemyHPzero,this,&GamePage::gameWin);

}

GamePage::~GamePage() {
    delete ui;
}
//按键处理
void GamePage::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        keyAPressed = true;
        break;
    case Qt::Key_D:
        keyDPressed = true;
        break;
    case Qt::Key_J:
        keyJPressed = true;
        break;
    case Qt::Key_K:
        keyKPressed = true;
        break;
    case Qt::Key_L:
        keyLPressed = true;
        break;
    }
}

void GamePage::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        keyAPressed = false;
        break;
    case Qt::Key_D:
        keyDPressed = false;
        break;
    case Qt::Key_J:
        keyJPressed = false;
        break;
    case Qt::Key_K:
        keyKPressed = false;
        break;
    case Qt::Key_L:
        keyLPressed = false;
        break;
    }
}

void GamePage::updateGame()
{
    //更新玩家状态
    if(liang->getState()==AnimState::Slash||liang->getState()==AnimState::Atked||liang->getState()==AnimState::Attack||liang->getState()==AnimState::Defence||liang->getState()==AnimState::Jump)
    {
        if(liang->getState()==AnimState::Atked)
        {
            liang->setState(AnimState::Atked);
        }
        else if(liang->getState()==AnimState::Attack)
        {
            liang->setState(AnimState::Attack);
        }
        else if(liang->getState()==AnimState::Defence)
        {
            liang->setState(AnimState::Defence);
        }
        else if(liang->getState()==AnimState::Jump)
        {
            liang->setState(AnimState::Jump);
        }
        else if(liang->getState()==AnimState::Slash)
        {
            liang->setState(AnimState::Slash);
        }
    }
    else
    {
        if(keyLPressed||keyKPressed||keyJPressed)
        {
            if(keyLPressed)
            {
                liang->setState(AnimState::Defence);
            }
            else if(keyJPressed)
            {
                liang->setState(AnimState::Attack);
                emit liang->atkLaunch();
            }
            else if(keyKPressed)
            {
                liang->setState(AnimState::Jump);
            }
        }
        else if(keyAPressed||keyDPressed)
        {
            liang->setState(AnimState::Run);
            if(keyAPressed)liang->setDirection(Direction::Left);
            else liang->setDirection(Direction::Right);
        }
        else liang->setState(AnimState::Idle);
    }
    // 更新玩家图像位置
    playerItem->setPos(liang->getX(), liang->getY());
    playerItem->setPixmap(liang->getCurrentImage());
    //更新受击判定rect位置
    liangRect.setX(liang->getX());
    enemyRect.setX(diren->getEX());
    swordAirRect.setX(liang->Air->x);
    //更新敌人状态
    if(diren->coolDownTimer->isActive())
    {

    }
    else
    {
        if(diren->EgetState()==EAnimState::Idle)
        {
            if(diren->EgetState()==EAnimState::Atked)
            {

            }
            else
            {
                randon = QRandomGenerator::global()->bounded(0,10);
                if(randon <= 3)
                {
                    diren->EsetState(EAnimState::Run);
                    if(liang->getX() < diren->getEX())
                    {
                        diren->EsetDirection(EDirection::Left);
                    }
                    else diren->EsetDirection(EDirection::Right);
                }
                else
                {
                    diren->EsetState(EAnimState::Attack);
                    emit diren->EatkLaunch();
                    if(liang->getX() < diren->getEX())
                    {
                        diren->EsetDirection(EDirection::Left);
                    }
                    else diren->EsetDirection(EDirection::Right);
                }
            }
        }
    }
    //更新敌人图像位置
    enemyItem->setPos(diren->getEX(),diren->getEY());
    enemyItem->setPixmap(diren->EgetCurrentImage());
    enemyRect.setX(diren->Ex);

    //更新剑气位置
    if(liang->Air->isLauched)
    {
        scene->addItem(airItem);
        liang->Air->x += liang->Air->Vx;
        airItem->setPixmap(liang->Air->getSwordAirImg());
        airItem->setPos(liang->Air->x,liang->Air->y);
        swordAirRect.setX(liang->Air->x);
    }
    else
    {

    }
    //检测血量是否达到胜负判定条件
    if(liang->HP<=0)
    {
        emit playerHPzero();
    }
    if(diren->E_HP<=0)
    {
        emit enemyHPzero();
    }
    //更新血条
    liangHP->setPos(0-int((400-liang->HP)*(675/400))-200,0);
    enemyHP->setPos(925+int((3000-diren->E_HP)*(675/3000)),0);
}
//剑气突破边缘处理
void GamePage::airClean()
{
    if(liang->Air->x >= 1600 || liang->Air->x <= 0)
    {
        liang->Air->Vx = 0;
        liang->Air->x = liang->getX();
        liang->Air->isLauched = false;
        liang->Air->isDamageMade = false;
        scene->removeItem(airItem);
    }
}
//判定玩家是否受击
void GamePage::doesPlayerAttcked()
{
    if(liang->getState()==AnimState::Defence)
    {
        liang->setState(AnimState::Slash);
        emit liang->slashLaunch();
    }
    else emit characterAttacked();
}
//判定敌人是否受到普通攻击
void GamePage::doesEnemyAirAttacked()
{
    if(liang->getDirection()==Direction::Left)
    {
        if(diren->getEX()<=liang->getX())emit enemyAirAttacked();
    }
    else
    {
        if(diren->getEX()>=liang->getX())emit enemyAirAttacked();
    }
}
//绘制反击特效
void GamePage::paintSlashEffect()
{
    scene->addItem(electricityEffectItem);
    if(liang->getDirection()==Direction::Left)
    {
        electricityEffectItem->setPos(liang->getX()+190-1000,liang->getY());
    }
    else
    {
        electricityEffectItem->setPixmap(effect->slashEffectImg.transformed(QTransform().scale(-1,1)));
        electricityEffectItem->setPos(liang->getX()+190,liang->getY());
    }
}
//移除反击特效
void GamePage::removeSlashEffect()
{
    scene->removeItem(electricityEffectItem);
}
//判定敌人是否收到反击攻击
void GamePage::doesEnemySlashAttacked()
{
    if(liang->getDirection()==Direction::Left)
    {
        if(diren->getEX()<=liang->getX())emit enemySlashAttacked();
    }
    else
    {
        if(diren->getEX()>=liang->getX())emit enemySlashAttacked();
    }
}
//游戏胜利
void GamePage::gameWin()
{
    emit theGameIsWin();
}
//游戏失败
void GamePage::gameLose()
{
    emit theGameIsLose();
}


