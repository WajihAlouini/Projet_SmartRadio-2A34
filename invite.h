#ifndef INVITE_H
#define INVITE_H
#include <QString>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QAudioInput>
#include <QFile>
#include <QMediaPlayer>

class invite
{
public:
    invite();
    invite(int,int,QDateTime);

    int getid();
    int getrep();
    QDateTime getdatetime();

    void setid(int);
    void setrep(int);
    void setdatetime(QDateTime);

    bool ajouter();
   QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier();
QSqlQueryModel* afficherech(QString,int);
QString recherchequestion(int);
QString rechercherep(int);
void playvideo();
bool checklogin(QString,QString);


private:
    int id,repetition;
    QDateTime datetime;};



#endif // INVITE_H
