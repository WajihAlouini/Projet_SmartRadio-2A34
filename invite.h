#ifndef INVITE_H
#define INVITE_H

#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QString>
#include <QSqlQueryModel>

class invite
{
public:
    invite();
    invite(QString,int,QDateTime);

    QString getnom();
    int getrep();
    QDateTime getdate();
    void setnom(QString);
    void setrep(int);
    void setdate(QDateTime);
    bool ajouter();
   QSqlQueryModel* afficher();
bool supprimer(QString);
bool modifier(QString,int,QDateTime);

private:
    int repetition;
    QString nom;
    QDateTime date;
};


#endif // INVITE_H
