#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>

class personnel
{
private:
    int ID,SALAIRE,alert;
   QString NOMP,PRENOM,FONCTION;
public:
    personnel();
    personnel( int, QString, QString, QString,int,int);
   int getid();
   int getsalaire();
    int getalert();
   QString getnom();
   QString getprenom();
   QString getfonction();

 void setid(int);
   void setsalaire( int);
    void setalert( int);
  void  setnom(QString);
void setprenom( QString);
  void  setfonction(QString);

   bool ajouter();
bool supprimer(int);
QSqlQueryModel*afficher();
bool modifier( int, QString, QString, QString,int,int);
QSqlQueryModel *trierpersonnel();
//QSqlQueryModel *personnel::rechercher(QString );
void rechercher(QString a,QTableView *g);
void erreur();
};

#endif // PERSONNEL_H
