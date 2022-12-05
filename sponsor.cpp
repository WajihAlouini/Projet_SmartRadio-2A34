#include "sponsor.h"
#include <QString>
#include "QSqlQuery"
#include <QtDebug>
#include <QSqlQueryModel>
sponsor::sponsor()
{
nom="";duree="";heure="";repetition=0;
}
sponsor::sponsor(QString nom,QString duree,QString heure,int repetition)
{this->nom=nom;this->duree=duree;this->heure=heure;this->repetition=repetition;}
QString sponsor::getnom(){return nom;}
QString sponsor::getduree(){return duree;}
QString sponsor::getheure(){return heure;}
int sponsor::getrepetition(){return repetition;}
void sponsor::setnom(QString nom){this->nom=nom;}
void sponsor::setduree(QString duree){this->duree=duree;}
void sponsor::setheure(QString heure){this->heure=heure;}
void sponsor::setrepetition(int repetition){this->repetition=repetition;}
bool sponsor::ajouter()
{
    QSqlQuery query;
          query.prepare("INSERT INTO sponsor (nom , duree , heure , repetition) "
                        "VALUES (:nom, :duree, :heure, :repetition)");
          query.bindValue(":nom",nom );
          query.bindValue(":duree", duree);
          query.bindValue(":heure", heure);
          query.bindValue(":repetition", repetition);

    return  query.exec();

}
bool sponsor::supprimer(QString nom)
{


    QSqlQuery query;

    query.prepare("Delete from sponsor where nom= :nom");
    query.bindValue(":nom",nom);

    return query.exec();
}
QSqlQueryModel * sponsor::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from sponsor");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("duree"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("heure"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("repetition"));
    return model;
}
bool sponsor::modifier(QString nom)
{

    QSqlQuery q;//requete SQL qui peut s'executer a partir du QT
    q.prepare("update sponsor set heure=:heure,duree=:duree,repetition=:repetition where nom=:nom");
    q.bindValue(":nom",nom);//injection SQL (securité) remplacement des tags ex::nom avec les valeurs
    q.bindValue(":heure",heure);
    q.bindValue(":duree",duree);
    q.bindValue(":repetition",repetition);

    return q.exec();//executer

}
QSqlQueryModel* sponsor::afficherTri()
{
    QSqlQueryModel * model=new QSqlQueryModel();

          model->setQuery("select * from sponsor order by nom" );

          model->setHeaderData(1,Qt::Horizontal,QObject::tr("duree"));

          model->setHeaderData(2,Qt::Horizontal,QObject::tr("heure"));

          model->setHeaderData(3,Qt::Horizontal,QObject::tr("repetition"));
            return model;
}
void sponsor::afficherRech(QString a, QTableView* g)
    {
        {
            QSqlQuery qry;
             QSqlQueryModel *m=new QSqlQueryModel();//initialisation
       qry.prepare("select * from sponsor where nom like '%"+a+"%' OR duree like '%"+a+"%' OR heure like '%"+a+"%' OR repetition like '%"+a+"%' ");
                         qry.exec();
                     m->setQuery(qry);
             g->setModel(m);


         }
    }
