#ifndef MENU_H
#define MENU_H
#include "mainwindow.h"
#include <QMainWindow>
#include "rana.h"
#include "salim.h"
#include "wajih.h"
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

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::menu *ui;
    Ui::MainWindow *uii;
 MainWindow * M;
  rana * R;
  salim *S;
  wajih *W;

};

#endif // MENU_H
