#ifndef ALERT_H
#define ALERT_H
#include <QString>
#include <QObject>

class alert
{
public:
    alert();
    QString Message();
    void SetMessage(QString Msg);
protected:
  QString mMessage ;
};

#endif // ALERT_H
