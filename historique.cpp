#include "historique.h"

#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QString>
#include <QObject>
#include<QDate>
#include "emission.h"
historique::historique()
{

}
historique::historique(QString type, int id, QString nom){
    this->typeh=type;
    this->idh=id;
    this->nomh=nom;
}

void historique::Ajouter()
{
    QSqlQuery query;
    QString res = QString::number(idh);
    query.prepare("insert into HISTORIQUE values (:type, :id, :nom)");
    query.bindValue(":type",typeh);
    query.bindValue(":id",idh);
    query.bindValue(":nom",nomh);
    query.exec();
}
QSqlQueryModel * historique::Afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * FROM HISTORIQUE;");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("type"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("id"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Nom"));

 return model;
}
