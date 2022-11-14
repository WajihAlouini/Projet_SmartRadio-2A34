#include "invite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include "mainwindow.h"
#include "mainwindow.cpp"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QTime>
#include <QTimeEdit>
#include <QAudioInput>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QVideoWidget>
#include <QVBoxLayout>
invite::invite()
{ repetition=0; id=0;
}

    invite::invite(int id,int repetition,QDateTime datetime){

        this->id=id;
        this->repetition=repetition;
        this->datetime=datetime;

    }
    int invite::getid(){return id;}
    int invite::getrep(){return repetition;}
    QDateTime invite::getdatetime(){return datetime;}
   void invite::setid(int id){this->id=id;}
    void invite::setrep(int repetition){this->repetition=repetition;}
    void invite::setdatetime(QDateTime datetime){this->datetime=datetime;}

    bool invite::ajouter()
    {
        QSqlQuery query;
        QString id_string= QString::number(id);
        QString rep_string= QString::number(repetition);


            query.prepare("INSERT INTO invite (ID, REPETITIONS, DATETIME) "
                          "VALUES (:id, :repetition, :datetime)");
            query.bindValue(":id", id_string);
            query.bindValue(":repetition", rep_string);
            query.bindValue(":datetime", datetime);




           return  query.exec();}
    QSqlQueryModel* invite::afficher(){


        QSqlQueryModel* model=new QSqlQueryModel();


              model->setQuery("SELECT * FROM invite");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("REPETITIONS"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATETIME"));



              return model;}
    bool invite::supprimer(int id){
        QSqlQuery query;
         QString id_string= QString::number(id);
        query.prepare("DELETE FROM invite WHERE ID=:id");
        query.bindValue(":id",id_string);
        return query.exec();
    }
    bool invite::modifier()
    {
        QSqlQuery query;
        invite I4;
         QString id_string= QString::number(id);
        QString repetition_string=QString::number(repetition);
       bool test=I4.afficherech(id_string,1);
       if(test==false)return query.exec();
       else{



        query.prepare("UPDATE invite SET ID =:id, REPETITIONS=:repetition, DATETIME=:datetime WHERE  ID = '"+id_string+"' ");
        query.bindValue(":id",id_string);
        query.bindValue(":repetition", repetition_string);
        query.bindValue(":datetime", datetime);
       }


        return query.exec();
        }
    QSqlQueryModel* invite::afficherech(QString mot,int choix){


    QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
    if (choix==1){

           model->setQuery("SELECT* FROM invite WHERE ID="+mot);
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("REPETITIONS"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATETIME"));


    }if (choix==2){

        model->setQuery("SELECT* FROM invite WHERE DATEI like mot");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("REPETITIONS"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATETIME"));


    }
    return model;
        }
    QString invite::recherchequestion(int id){
        QSqlQuery query;
        QString quest;
        query.prepare("select* from ENIGME WHERE ID=:ID ");
        query.bindValue(":ID",id);
query.exec();
        while(query.next())
       {
           quest=(query.value("QUESTION").toString());

        }



        return quest;

    }

    QString invite::rechercherep(int id){
 QSqlQuery query;
 QString rep;

 query.prepare("select* from ENIGME WHERE ID=:ID ");
 query.bindValue(":ID",id);
query.exec();
 while(query.next())
{
    rep=(query.value("REPONSE").toString());

 }
return rep;

    }
   void invite::playvideo(){
        QMediaPlayer* player = new QMediaPlayer();
        QVideoWidget* vw= new QVideoWidget;
        player->setVideoOutput(vw);
        player->setMedia(QUrl("qrc:/Video/Sound.mp4"));
        vw->setGeometry(100,100,300,400);
        vw->show();
        player->play();


    qDebug()<<player->state();
    }

