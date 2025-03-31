#ifndef LOSEPAGE_H
#define LOSEPAGE_H

#include <QWidget>

namespace Ui {
class losePage;
}

class losePage : public QWidget
{
    Q_OBJECT

public:
    explicit losePage(QWidget *parent = nullptr);
    ~losePage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::losePage *ui;
};

#endif // LOSEPAGE_H
