#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include<QString>
#include "alert.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget *VW =new QVideoWidget;
player ->setVideoOutput(VW);
player->setMedia(QUrl("qrc:/un chat qui dance"));
VW->setGeometry(100,200,300,400);
VW->show();
player->play();

 qDebug() <<player->state();

    return a.exec();
}
