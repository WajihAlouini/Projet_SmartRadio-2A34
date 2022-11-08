#include "emission.h"

Emission::Emission()
{

}
Emission::Emission(int id, QString nom,QString heure,QString type,int duree)
{
    this->id=id;
    this->nom=nom;
    this->heure=heure;
    this->type=type;
    this->duree=duree;
}
bool Emission::ajouter(){
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("insert into EMISSION values (:id, :nom, :heure,:type,:duree)");
    query.bindValue(":id",res);
    query.bindValue(":nom", nom);
    query.bindValue(":heure",heure);
    query.bindValue(":type",type );
    query.bindValue(":duree",duree);

    return query.exec();
}
QSqlQueryModel * Emission::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMISSION");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("HEURE"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("DUREE"));

    return model;
}
bool Emission::supprimer(int id){
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("delete from emission where ID = :id");
    query.bindValue(":id", res);
    return query.exec();
}
bool Emission::modifier(int id,QString nom,QString heure,QString type,int duree){
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("UPDATE EMISSION SET NOM=:nom , HEURE=:heure,TYPE=:type,DUREE=:duree WHERE ID=:id");
    query.bindValue(":id",id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":heure", heure);
    query.bindValue(":type", type);
    query.bindValue(":duree", duree);
    return query.exec();
}
QSqlQueryModel * Emission::trier(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from EMISSION order by "+tri_par+" "+type_tri+" ");
    return model;
}
QSqlQueryModel * Emission::recherche(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from emission where  (id) LIKE '%"+rech+"%' ");
    return model;
}








