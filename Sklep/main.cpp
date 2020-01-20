#include "mainwindow.h"
#include <QApplication>
#include "externs.h"

extern QSqlDatabase db;
extern void connection();
extern void close();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection();
    MainWindow w;
    w.show();
    //close();

    return a.exec();
}
