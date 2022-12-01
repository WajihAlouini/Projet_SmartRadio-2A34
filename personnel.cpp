#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
personnel::personnel()
{
 ID=0;
NOMP="";
PRENOM="";
FONCTION="";
SALAIRE=0;
}
personnel::personnel(int ID , QString NOMP, QString PRENOM, QString FONCTION, int SALAIRE)
{
this->ID=ID;
    this->NOMP=NOMP;
    this->PRENOM=PRENOM;
    this->FONCTION=FONCTION;
    this->SALAIRE=SALAIRE;

}
int personnel::getid(){return ID;}
QString personnel::getnom(){return NOMP;}
QString personnel::getprenom(){return PRENOM;}
 QString personnel::getfonction(){return FONCTION;}
int  personnel::getsalaire(){return SALAIRE;}

void personnel::setid (int ID){this->ID=ID;}
void personnel::setnom(QString NOMP){this->NOMP=NOMP;}
void personnel::setprenom(QString PRENOM){this->PRENOM=PRENOM;}
void personnel::setfonction(QString FONCTION){this->FONCTION=FONCTION;}
void personnel::setsalaire(int SALAIRE){ this->SALAIRE=SALAIRE;}

bool personnel::ajouter()
{
 QSqlQuery query ;
 QString id_string =QString ::number(ID);

    query.prepare ("INSERT  INTO PERSONNEL (ID,NOMP,PRENOM,FONCTION,SALAIRE)" "values(:id_string,:nomp,:prenom,:fonction,:salaire)");

query.bindValue(":id_string",ID);
query.bindValue(":nomp",NOMP);
query.bindValue(":prenom",PRENOM);
query.bindValue(":fonction",FONCTION);
query.bindValue(":salaire",SALAIRE);
 return query.exec();
}

bool personnel::supprimer(int ID)
{

    QSqlQuery query;
QString id_string =QString ::number(ID);
            query.prepare("DELETE from personnel where ID=:id");
   query.bindValue(":id",id_string);
    return query.exec();
}

QSqlQueryModel * personnel::afficher()
{
 QSqlQueryModel * model=new  QSqlQueryModel();
 model->setQuery("SELECT *FROM PERSONNEL");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMP"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("FONCTION"));
 model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));

 return model;
}
bool personnel::modifier(int ID, QString NOMP, QString PRENOM, QString FONCTION, int SALAIRE)
{

            QSqlQuery query;

            QString id_string =QString::number(ID);
            query.prepare("UPDATE PERSONNEL SET NOMP=:nomp,PRENOM=:prenom,FONCTION=:fonction,SALAIRE=:salaire, WHERE ID=:id");

            query.bindValue(":id", id_string);
            query.bindValue(":nomp", NOMP);
            query.bindValue(":prenom", PRENOM);
            query.bindValue(":fonction", FONCTION);
            query.bindValue(":salaire",SALAIRE);
            return  query.exec();}

void personnel::rechercher(QString a,QTableView *g )
    { {QSqlQuery qry;
             QSqlQueryModel *m=new QSqlQueryModel();//initialisation
             qry.prepare("select * from personnel where NOMP='"+a+"'");
             qry.exec();
                     m->setQuery(qry);
             g->setModel(m);

         }}



