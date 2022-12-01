#ifndef EMISSION_H
#define EMISSION_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QDate>

class Emission
{
public:
    Emission();
    Emission(int,QString,QString,QString,int,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int,int);
    QSqlQueryModel * trier(QString, QString);
    QSqlQueryModel * recherche(QString);
    void statistique(QVector<double>* ticks,QVector<QString> *labels);
    QSqlQueryModel *afficher_calendrier(QDate x);


private:
    int id;
    QString nom;
    QString heure;
    QString type;
    int duree;
    int nb_view;
};

#endif // EMISSION_H
