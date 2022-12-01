#ifndef CHATBOX_H
#define CHATBOX_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class chatbox
{
public:
    chatbox();
    chatbox (QString, QString, QString);
    QSqlQuery afficherChat(QString);
   QSqlQuery  envoyerchat();

private:
 QString nickname,Conversation,message_sent;
};

#endif // CHATBOX_H
