#include "alert.h"
#include "connection.h"
#include <QDebug>
#include<QMessageBox>
alert::alert()
{

}

QString alert::Message()
{
    qDebug() <<  " commencement";
    try
    {
        QSqlQuery Query;
        Query.prepare("select * FROM personnel where ID=:id and alert='1'");

       alert  *cErr =new alert();


       throw cErr;
    throw QString("erreur de song");

    }

    catch ( char* cerr)
    {
     qDebug()<< cerr;
   }

     catch (QString sErr )
    {
     qDebug()<<" QString = " <<sErr;

    }

    catch (alert * cErrMsg )
   {
    qDebug()<<" alert = " << cErrMsg ->Message();

   }

    catch(...)
    {
      qDebug()  <<" ERREUR inconnut ";

    }
   qDebug() <<  "ERREUR connut ";
   }
void alert::SetMessage(QString Msg)
{
   mMessage=Msg;
}
