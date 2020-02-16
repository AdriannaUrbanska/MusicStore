#ifndef EXTERNS_H
#define EXTERNS_H

#include <QSqlDatabase>
#include <QDebug>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

/**
 * Funkcja nawiązująca połączenie z bazą danych
 */
void connection()
{
    db.setConnectOptions();
    db.setHostName("localhost");
    db.setDatabaseName("u7urbanska");
    db.setUserName("u7urbanska");
    db.setPassword("7urbanska");
    db.setPort(54320);
    bool ok = db.open();

    if(ok)
        qDebug()<<"OK\n";
    else
        qDebug()<<"ERROR\n";

}

void close() {db.close();}

#endif // EXTERNS_H
