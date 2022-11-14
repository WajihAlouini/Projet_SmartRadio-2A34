#include "windowlogin.h"
#include "ui_windowlogin.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QWidget>
#include <QMessageBox>

windowlogin::windowlogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowlogin)
{
    ui->setupUi(this);

}

windowlogin::~windowlogin()
{
    delete ui;

}

bool windowlogin::checklogin(QString n,QString p){

QSqlQuery qry;
bool test;
qry.prepare("SELECT* FROM LOGIN WHERE USERNAME = :name AND PASSWORD = :pass");
qry.bindValue(":name", n);
qry.bindValue(":pass", p);
qry.exec();
if(qry.next()){
    test=true;
}
else {test=false;}
return test;}

void windowlogin::on_button_login_clicked()
{
QString n=ui->username->text();
QString p=ui->password->text();
   bool I6=checklogin(n,p);
   if(I6==true)
   {
       mainwindow = new MainWindow(this);
       mainwindow->show();
   }
else
   {QMessageBox::critical(nullptr, QObject::tr("erreur login"),
                                      QObject::tr("erreur login"), QMessageBox::Cancel);}




}
