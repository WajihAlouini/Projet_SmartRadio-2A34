#include "invite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDateTime>
#include "mainwindow.h"
#include "mainwindow.cpp"
#include "invite.h"
#include "ui_mainwindow.h"
invite::invite()
{ repetition=0; nom="";}

    invite::invite(QString nom,int repetition,QDateTime date){

        this->nom=nom;
          this->repetition=repetition;
        this->date=date;
    }
    QString invite::getnom(){return nom;}
    int invite::getrep(){return repetition;}
    QDateTime invite::getdate(){return date;}
    void invite::setnom(QString nom){this->nom=nom;}
    void invite::setrep(int repetition){this->repetition=repetition;}
    void invite::setdate(QDateTime date){this->date=date;}
    bool invite::ajouter()
    {bool test=false;
        QSqlQuery query;
        QString rep_string= QString::number(repetition);
            query.prepare("INSERT INTO invite (NOM, REPETITIONS, DATETIME) "
                          "VALUES (:nom, :repetition, :date)");
            query.bindValue(":nom", nom);
            query.bindValue(":repetition", rep_string);
            query.bindValue(":date", date);
           return  query.exec();}
    QSqlQueryModel* invite::afficher(){


        QSqlQueryModel* model=new QSqlQueryModel();


              model->setQuery("SELECT * FROM invite");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("REPETITIONS"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATETIME"));


              return model;}
    bool invite::supprimer(QString nom){
        QSqlQuery query;
        query.prepare("DELETE FROM invite WHERE NOM=:nom");
        query.bindValue(":nom",nom);
        return query.exec();
    }
    bool invite::modifier(QString nom,int repetition,QDateTime date)
    {
        QSqlQuery query;
        QString repetition_string=QString::number(repetition);
        query.prepare("UPDATE invite SET nom =:nom, repartition=:repartition, date=:date WHERE nom=:nom");
        query.bindValue(":nom",nom);
        query.bindValue(":repartition", repetition_string);
        query.bindValue(":date", date);

        return  query.exec();
        }
