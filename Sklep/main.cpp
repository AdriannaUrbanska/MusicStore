#include "mainwindow.h"
#include <QApplication>
#include "externs.h"
#include "polaczenie.h"
#include <QDebug>

extern QSqlDatabase db;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Polaczenie p;
    p.show();
    bool ok = true;

    if(ok)
    {
        MainWindow w;
        w.show();
    }
    else
        qDebug()<<"BLAD";

    return a.exec();
}
