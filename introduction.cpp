#include "introduction.h"
#include "ui_introduction.h"

#include <QFont>

Introduction::Introduction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Introduction)
{
    ui->setupUi(this);

    this->setWindowTitle("游戏说明");
    this->setWindowIcon(QIcon(ICON_PATH));

    this->setFixedSize(1462,902);
    bg.load(INTRO_BG_PICTRUE_PATH);
    ui->bgLabel->setFixedSize(1462,902);
    ui->bgLabel->setPixmap(bg);
    ui->bgLabel->setScaledContents(true);

    QFont font("华文楷体",40,30,0);
    ui->textLabel->setFont(font);
    ui->textLabel->setFixedSize(1462,902);

    ui->textLabel->setWordWrap(true);
    ui->textLabel->setText("<p style='color:white;'>这是一个基于国产gal《饿殍：明末千里行》的自制二创小游戏</p>"
                           "<p style='color:white;'>在这里，你将扮演“良”这一角色参与明末起义军，兑现你与满穗的诺言</p>"
                           "<h3 style='color:white;'>操作方式</h3>"
                           "<p style='color:white;'>移动：WASD</p>"
                           "<p style='color:white;'>攻击：J</p>"
                           "<p style='color:white;'>跳跃：K</p>"
                           "<p style='color:white;'>格挡：L</p>");
    ui->textLabel->setContentsMargins(10, 10, 10, 10);
}

Introduction::~Introduction()
{
    delete ui;
}
