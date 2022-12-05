#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}

void notification::notificationC()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/USER/Desktop/notif"));

    notifyIcon->show();
    notifyIcon->showMessage("Attention ","La date du mariage la plus proche est 10/08/2023",QSystemTrayIcon::Information,15000);
}
