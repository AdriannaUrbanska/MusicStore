#ifndef EXTERNS_H
#define EXTERNS_H

#include <QSqlDatabase>
#include <QDebug>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

void connection()
{
    db.setConnectOptions();
    db.setHostName("localhost");
    db.setDatabaseName("project");
    db.setUserName("urbanska");
    db.setPassword("project");
    db.setPort(5432);
    bool ok = db.open();

    if(ok)
        qDebug()<<"OK\n";
    else
        qDebug()<<"ERROR\n";

}

void close() {db.close();}

#endif // EXTERNS_H
