#ifndef EXTERNS_H
#define EXTERNS_H

#include <QSqlDatabase>
#include <QDebug>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
QString baza;
QString host;
int port;
QString nazwa;
QString haslo;
bool ok;

/**
 * Funkcja nawiązująca połączenie z bazą danych
 */
bool connection()
{
    db.setConnectOptions();
    db.setHostName(host);
    db.setDatabaseName(baza);
    db.setUserName(nazwa);
    db.setPassword(haslo);
    db.setPort(port);

    bool polaczenie = db.open();

    qDebug()<<"BAZA "<<baza;
    return polaczenie;
}

void close() {db.close();}

#endif // EXTERNS_H
