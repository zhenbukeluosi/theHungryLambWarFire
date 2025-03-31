#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QApplication>
#include <QMediaPlayer>

#include "config.h"
#include "introduction.h"
#include "gamepage.h"
#include "winpage.h"
#include "losepage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap background;

    void open();

    WinPage *winpage;
    losePage *losepage;

    Introduction *intro;
    GamePage *gamepage;

private slots:
    void on_GameStart_clicked();

    void on_Intro_clicked();

    void on_Quit_clicked();

    void on_musicBtn_clicked();

    void handleGameWin();

    void handleGameLose();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
