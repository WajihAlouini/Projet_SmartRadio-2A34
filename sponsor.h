
#ifndef SPONSOR_H
#define SPONSOR_H
#include <QString>
#include <QSqlQueryModel>
#include <QTableView>
class sponsor
{
public:
    sponsor();
    sponsor(QString,QString,QString,int);
    QString getnom();
    QString getduree();
    QString getheure();
    int getrepetition();
    void setnom(QString);
    void setduree(QString);
    void setheure(QString);
    void setrepetition(int);
    bool ajouter();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel * afficher();
    void afficherRech(QString a,QTableView* g);
    QSqlQueryModel* afficherTri();
private:
    int repetition ;
    QString nom,duree,heure;
};

#endif // SPONSOR_H
