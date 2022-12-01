#include "chatbox.h"

chatbox::chatbox()
{

}

chatbox::chatbox(QString nickname, QString Conversation, QString message_sent)
{
    this->nickname = nickname;
    this->Conversation = Conversation;
    this->message_sent = message_sent;

}
QSqlQuery chatbox::envoyerchat()
 {
    QSqlQuery query;
    query.prepare("insert into CHATBOX values (:nickname, :conversation, CHATBOX_SEQ.nextval, :message_sent, sysdate); ");
    query.bindValue(":NICKNAME", nickname);
    query.bindValue(":CONVERSATION", Conversation);
    query.bindValue(":MESSAGE_SENT", message_sent);
    return query;
}

QSqlQuery chatbox::afficherChat(QString Conversation){
    QSqlQuery query;

    query.prepare("select  NICKNAME, MSG, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+"   date_sent; ");
    return query;
}
