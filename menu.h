#ifndef MENU_H
#define MENU_H
#include "mainwindow.h"
#include <QMainWindow>
#include "rana.h"
namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    Ui::MainWindow *uii;
 MainWindow * M;
  rana * R;
};

#endif // MENU_H
