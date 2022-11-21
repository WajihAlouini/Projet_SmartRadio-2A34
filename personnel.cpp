#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include "alert.h"
personnel::personnel()
{
 ID=0;
NOMP="";
PRENOM="";
FONCTION="";
SALAIRE=0;
alert=0 | 1;
}
personnel::personnel(int ID , QString NOMP, QString PRENOM, QString FONCTION, int SALAIRE,int alert)
{
this->ID=ID;
    this->NOMP=NOMP;
    this->PRENOM=PRENOM;
    this->FONCTION=FONCTION;
    this->SALAIRE=SALAIRE;
    this->alert=alert;
}
int personnel::getid(){return ID;}
QString personnel::getnom(){return NOMP;}
QString personnel::getprenom(){return PRENOM;}
 QString personnel::getfonction(){return FONCTION;}
int  personnel::getsalaire(){return SALAIRE;}
 int personnel::getalert(){return alert;}
void personnel::setid (int ID){this->ID=ID;}
void personnel::setnom(QString NOMP){this->NOMP=NOMP;}
void personnel::setprenom(QString PRENOM){this->PRENOM=PRENOM;}
void personnel::setfonction(QString FONCTION){this->FONCTION=FONCTION;}
void personnel::setsalaire(int SALAIRE){ this->SALAIRE=SALAIRE;}
void personnel::setalert(int alert){ this->alert=alert;}
bool personnel::ajouter()
{
 QSqlQuery query ;
 QString id_string =QString ::number(ID);

    query.prepare ("INSERT  INTO PERSONNEL (ID,NOMP,PRENOM,FONCTION,SALAIRE,ALERT)" "values(:id_string,:nomp,:prenom,:fonction,:salaire,:alert)");

query.bindValue(":id_string",ID);
query.bindValue(":nomp",NOMP);
query.bindValue(":prenom",PRENOM);
query.bindValue(":fonction",FONCTION);
query.bindValue(":salaire",SALAIRE);
query.bindValue(":alert",alert);
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
 model->setQuery("select *from personnel");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMP"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("FONCTION"));
 model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("alert"));
 return model;
}
bool personnel::modifier(int ID, QString NOMP, QString PRENOM, QString FONCTION, int SALAIRE,int alert)
{

            QSqlQuery query;

            QString id_string =QString::number(ID);
            query.prepare("UPDATE personnel SET NOMP=:nomp ,PRENOM=:prenom,FONCTION=:fonction,SALAIRE=:salaire,alert=:alert WHERE ID=:id");

            query.bindValue(":id", id_string);
            query.bindValue(":nomp", NOMP);
            query.bindValue(":prenom", PRENOM);
            query.bindValue(":fonction", FONCTION);
            query.bindValue(":salaire",SALAIRE);
query.bindValue(":alert",alert);
            return  query.exec();}

void personnel::rechercher(QString a,QTableView *g )
    { {QSqlQuery qry;
             QSqlQueryModel *m=new QSqlQueryModel();//initialisation
             qry.prepare("select * from personnel where NOMP='"+a+"'");
     //a,QTableView *g      NOMP like '%"+a+"%' OR PRENOM like '%"+a+"%' OR ID like '%"+a+"%'OR SALAIRE like '%"+a+"%'like FONCTION like '%"+a+"%' OR ALERT like '%"+a+"%'
             qry.exec();
                     m->setQuery(qry);
             g->setModel(m);

         }}



