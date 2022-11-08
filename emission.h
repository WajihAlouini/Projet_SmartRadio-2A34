#ifndef EMISSION_H
#define EMISSION_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>

class Emission
{
public:
    Emission();
    Emission(int,QString,QString,QString,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int);
    QSqlQueryModel * trier(QString, QString);
    QSqlQueryModel * recherche(QString);


private:
    int id;
    QString nom;
    QString heure;
    QString type;
    int duree;
};

#endif // EMISSION_H
