#include "emission.h"

Emission::Emission()
{

}
Emission::Emission(int id, QString nom,QString heure,QString type,int duree, int nb_view)
{
    this->id=id;
    this->nom=nom;
    this->heure=heure;
    this->type=type;
    this->duree=duree;
    this->nb_view=nb_view;
}
bool Emission::ajouter(){
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("insert into EMISSION values (:id, :nom, :heure,:type,:duree,:nb_view)");
    query.bindValue(":id",res);
    query.bindValue(":nom", nom);
    query.bindValue(":heure",heure);
    query.bindValue(":type",type );
    query.bindValue(":duree",duree);
    query.bindValue(":nb_view",nb_view);

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
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("NB_VIEW"));

    return model;
}
bool Emission::supprimer(int id){
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("delete from emission where ID = :id");
    query.bindValue(":id", res);
    return query.exec();
}
bool Emission::modifier(int id,QString nom,QString heure,QString type,int duree,int nb_view){
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("UPDATE EMISSION SET NOM=:nom , HEURE=:heure,TYPE=:type,DUREE=:duree,NB_VIEW=:nb_view WHERE ID=:id");
    query.bindValue(":id",id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":heure", heure);
    query.bindValue(":type", type);
    query.bindValue(":duree", duree);
    query.bindValue(":nb_view", nb_view);
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
void Emission::statistique(QVector<double>* ticks,QVector<QString> *labels)
{   QSqlQuery q;
    int i=0;
    q.exec("select emission where (type) LIKE 'sport','politique',culture");
    while (q.next()) {
        QString refer = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<refer;
}
}


QSqlQueryModel *Emission::afficher_calendrier(QDate x)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        QString x1=QString::number(x.month()),x2=QString::number(x.day()),x3=QString::number(x.year());
        model->setQuery("select ID,NOM,TYPE from EMISSION where(extract(day from HEURE)='"+x2+"' and extract(month from HEURE)='"+x1+"' and extract(year from HEURE)='"+x3+"')");
        model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2,Qt::Horizontal, QObject::tr("TYPE"));

        return model;
}







