#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"
menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    M=new MainWindow (this);
    M-> show();
}

void menu::on_pushButton_2_clicked()
{
   R=new rana (this);
    R-> show();
}

void menu::on_pushButton_4_clicked()
{
    S=new salim(this);
     S-> show();
}


void menu::on_pushButton_3_clicked()
{
    W=new wajih(this);
            W->show();
}
