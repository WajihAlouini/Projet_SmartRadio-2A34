#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "emission.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(EM.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_Nom->text();
    QString heure = ui->lineEdit_Heure->text();
    QString type = ui->lineEdit_Type->text();
    int duree = ui->lineEdit_Duree->text().toInt();


    Emission E(id, nom,heure,type,duree );
    bool test = E.ajouter();

    if (test){
        ui->tableView->setModel(EM.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();
    bool test = EM.supprimer(id);

    if (test){
        ui->tableView->setModel(EM.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    Emission E2;
    int id = ui->lineEdit_ID_M->text().toInt();
    QString nom = ui->lineEdit_Nom_M->text();
    QString heure = ui->lineEdit_Heure_M->text();
    QString type = ui->lineEdit_Type_M->text();
    int duree = ui->lineEdit_Duree_M->text().toInt();


    bool test = E2.modifier( id,nom,heure,type,duree);
    if (test){

        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("modification effectué"),
                              QMessageBox::Ok
                              );
        ui->tableView->setModel(E2.afficher());
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}



void MainWindow::on_pushButton_Actualiser_clicked()
{
    ui->tableView->setModel(EM.afficher());

}



void MainWindow::on_pushButton_Chercher_clicked()
{
    QString rech_field = ui->lineEdit_Recherche->text();
    ui->tableView->setModel(EM.recherche(rech_field));

}


void MainWindow::on_pushButton_Trier__clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri->currentText();
    ui->tableView->setModel(EM.trier(type_of_tri, tri_par));
}
