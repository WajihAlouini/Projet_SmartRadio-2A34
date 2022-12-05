#ifndef HISTORIQUE_H
#define HISTORIQUE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "emission.h"
class historique
{

public:
    historique();

    historique(QString type, int id, QString nom);
    void Ajouter();
    QSqlQueryModel * Afficher();
private:
int idh;
QString nomh,typeh;
};

#endif // HISTORIQUE_H
