#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->open();
}

void MainWindow::open()
{
    setFixedSize(1600,900);
    setWindowTitle("饿殍：烽火");
    this->setWindowIcon(QIcon(ICON_PATH));
    background.load(BG_PICTRUE_PATH);



    QFont font("隶书",30,10,0);

    ui->GameStart->setFont(font);
    ui->Intro->setFont(font);
    ui->Quit->setFont(font);

    ui->GameStart->move(600,200);
    ui->Intro->move(600,400);
    ui->Quit->move(600,600);

    ui->bgLabel->setPixmap(background);
    ui->bgLabel->setFixedSize(1600,900);
    ui->bgLabel->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GameStart_clicked()
{
    gamepage = new GamePage;
    gamepage->setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(gamepage,&GamePage::theGameIsWin,this,&MainWindow::handleGameWin);
    connect(gamepage,&GamePage::theGameIsLose,this,&MainWindow::handleGameLose);

    gamepage->show();
}


void MainWindow::on_Intro_clicked()
{
    intro = new Introduction;
    intro->setWindowFlags(Qt::WindowStaysOnTopHint);
    intro->show();
}


void MainWindow::on_Quit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_musicBtn_clicked()
{

}

void MainWindow::handleGameWin()
{
    winpage = new WinPage;
    winpage->show();
    gamepage->deleteLater();
}

void MainWindow::handleGameLose()
{
    losepage = new losePage;
    losepage->show();
    gamepage->deleteLater();
}
