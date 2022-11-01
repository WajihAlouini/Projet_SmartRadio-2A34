#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invite.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_invite->setModel(I.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{ QString nom=ui->le_nom->text();
    int repetition=ui->le_rep->text().toInt();
    QDateTime date=ui->la_date->dateTime();
    invite I(nom,repetition,date);
    bool test=I.ajouter();
    if (test)
    {ui->tab_invite->setModel(I.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Ajout effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);


              }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }








void MainWindow::on_pb_supprimer_clicked()
{
    invite I1;
    I1.setnom(ui->le_nom_supp->text());
    bool test=I1.supprimer(I1.getnom());
    QMessageBox msgBox;
    if (test)
    {msgBox.setText("Suppression avec succes");
    ui->tab_invite->setModel(I1.afficher());}
    else msgBox.setText("Echec de suppression");
    msgBox.exec();
}
void MainWindow::on_pb_modifier_clicked()
{ invite I2;
     int repetition=ui->le_nvrep->text().toInt();
    QString nom=ui->le_nvnom->text();
   QDateTime date=ui->la_nvdate->dateTime();
     bool test=I2.modifier(nom,repetition,date);
     if (test){
 ui->tab_invite->setModel(I2.afficher());
         QMessageBox::information(nullptr, QObject::tr(" OK"),
                     QObject::tr("modifier successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
     else
     {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("modifier failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);}
}

