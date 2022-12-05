#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>

class personnel
{
private:
    int ID,SALAIRE;
   QString NOMP,PRENOM,FONCTION;
public:
    personnel();
    personnel( int, QString, QString, QString,int);
   int getid();
   int getsalaire();
   QString getnom();
   QString getprenom();
   QString getfonction();

 void setid(int);
   void setsalaire( int);
  void  setnom(QString);
void setprenom( QString);
  void  setfonction(QString);

   bool ajouter();
bool supprimer(int);
QSqlQueryModel*afficher();
bool modifier( QString, QString, QString, QString,QString);
QSqlQueryModel *trierpersonnel();

void rechercher(QString a,QTableView *g);

};

#endif // PERSONNEL_H
