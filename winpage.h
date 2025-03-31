#ifndef WINPAGE_H
#define WINPAGE_H

#include <QWidget>

namespace Ui {
class WinPage;
}

class WinPage : public QWidget
{
    Q_OBJECT

public:
    explicit WinPage(QWidget *parent = nullptr);
    ~WinPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WinPage *ui;
};

#endif // WINPAGE_H
