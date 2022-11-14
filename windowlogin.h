#ifndef WINDOWLOGIN_H
#define WINDOWLOGIN_H
#include "mainwindow.h"
#include <QDialog>

#include <QWidget>

namespace Ui {
class windowlogin;
}

class windowlogin : public QWidget
{
    Q_OBJECT

public:
    explicit windowlogin(QWidget *parent = nullptr);
    ~windowlogin();
    bool checklogin(QString,QString);

private slots:
    void on_button_login_clicked();

private:
    Ui::windowlogin *ui;
    MainWindow* mainwindow;

};

#endif // WINDOWLOGIN_H
