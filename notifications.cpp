#include "notifications.h"

#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}
void notification::notification_ajout()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->showMessage("personnel "," personnel ajouté",QSystemTrayIcon::Information,15000);
}
void notification::notification_supprimer()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->showMessage("personnel ","personnel suprimé",QSystemTrayIcon::Information,15000);
}
void notification::notification_modifier()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->showMessage("personnel ","personnel modifié ",QSystemTrayIcon::Information,15000);
}
