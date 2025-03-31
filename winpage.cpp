#include "winpage.h"
#include "ui_winpage.h"

WinPage::WinPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WinPage)
{
    ui->setupUi(this);
    this->setFixedSize(1600,900);

    ui->pushButton->resize(200,100);
    ui->pushButton->move(700,600);

    QFont font("隶书",30,10,0);

    ui->label->setText("恭喜你赢得胜利");
    ui->label->setFont(font);
    ui->label->setFixedSize(500,500);

    ui->pushButton->setFont(font);

    ui->label->move(650,0);
}

WinPage::~WinPage()
{
    delete ui;
}

void WinPage::on_pushButton_clicked()
{
    this->hide();
}
