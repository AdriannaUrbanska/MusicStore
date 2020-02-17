#include "polaczenie.h"
#include "ui_polaczenie.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

extern QSqlDatabase db;
extern QString baza;
extern QString host;
extern int port;
extern QString nazwa;
extern QString haslo;
extern bool connection();
extern bool ok;

Polaczenie::Polaczenie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polaczenie)
{
    ui->setupUi(this);
    this->setWindowTitle("Połąćzenie z bazą");
}

Polaczenie::~Polaczenie()
{
    delete ui;
}

void Polaczenie::on_polacz_clicked()
{
    baza = ui->baza->text();
    host = ui->host->text();
    port = ui->port->value();
    nazwa = ui->nazwa->text();
    haslo = ui->haslo->text();
    ok = connection();

    if(ok)
    {
        QMessageBox::information(this, "Połączenie", "Połączono z bazą!");
        w = new MainWindow(this);
        w->show();
    }
    else
        QMessageBox::warning(this, "Połączenie", "Błąd połączenia z bazą!");


}
