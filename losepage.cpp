#include "losepage.h"
#include "ui_losepage.h"

losePage::losePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::losePage)
{

    ui->setupUi(this);
    this->setFixedSize(1600,900);

    ui->pushButton->resize(200,100);
    ui->pushButton->move(700,600);

    QFont font("隶书",30,10,0);

    ui->label->setText("<p>胜败乃兵家常事</p>"
                       "<p>大侠请重新来过</p>");
    ui->label->setFont(font);
    ui->label->setFixedSize(1600,500);

    ui->label->move(650,0);

    ui->pushButton->setFont(font);
}

losePage::~losePage()
{
    delete ui;
}

void losePage::on_pushButton_clicked()
{
    this->hide();
}
