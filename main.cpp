#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include<QString>
#include<QDebug>
#include "menu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    bool test=c.createconnect();
    MainWindow w;
menu M;
    if(test )
    {M.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);





    return a.exec();
}
