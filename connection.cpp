#include "connection.h"

Connection::Connection(){
}

bool Connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("projet");
    db.setUserName("system");
    db.setPassword("211JFT0381");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
