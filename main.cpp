#include "mainwindow.h"
#include "QApplication"
#include "connection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    bool test = c.createconnection();
    MainWindow w;
    if (test){
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Connection successful"),
                              QMessageBox::Ok
                              );


    }else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed"),
                              QMessageBox::Cancel
                              );
    }
    return a.exec();

}
