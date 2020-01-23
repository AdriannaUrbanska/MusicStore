#include "zamowienia_pracownik.h"
#include "ui_zamowienia_pracownik.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

extern QSqlDatabase db;

Zamowienia_pracownik::Zamowienia_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienia_pracownik)
{
    ui->setupUi(this);
    this->setWindowTitle("Zamówienia");

    ui->tab_w_trakcie->setColumnWidth(0,40);
    ui->tab_w_trakcie->setColumnWidth(1,100);
    ui->tab_w_trakcie->setColumnWidth(2,100);
    ui->tab_w_trakcie->setColumnWidth(3,60);
    ui->tab_w_trakcie->setColumnWidth(4,100);
    ui->tab_w_trakcie->setColumnWidth(5,150);

    ui->tab_zrealizowane->setColumnWidth(0,40);
    ui->tab_zrealizowane->setColumnWidth(1,100);
    ui->tab_zrealizowane->setColumnWidth(2,100);
    ui->tab_zrealizowane->setColumnWidth(3,60);
    ui->tab_zrealizowane->setColumnWidth(4,100);
    ui->tab_zrealizowane->setColumnWidth(5,150);

    ui->tab->setCurrentIndex(0);

    ui->tab_zrealizowane->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_zrealizowane->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_zrealizowane->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tab_w_trakcie->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_w_trakcie->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_w_trakcie->setSelectionMode(QAbstractItemView::SingleSelection);

    zamowienia();

    ui->tab->setCurrentIndex(0);
    ui->tab_zrealizowane->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_zrealizowane->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_zrealizowane->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_zrealizowane->selectRow(0);

    ui->tab_w_trakcie->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_w_trakcie->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_w_trakcie->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_w_trakcie->selectRow(0);

    if(ui->tab_w_trakcie->rowCount() == 0)
        ui->oznacz->setDisabled(true);
}

Zamowienia_pracownik::~Zamowienia_pracownik()
{
    delete ui;
}

void Zamowienia_pracownik::on_powrot_clicked()
{
    this->close();
}

void Zamowienia_pracownik::zamowienia()
{
    int i_w_trakcie = 0;
    int i_zrealizowane = 0;

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM wszystkie_zamowienia()"))
    {
        while(query.next())
        {
            if(query.value(5).toString() == "W trakcie realizacji")
            {
                ui->tab_w_trakcie->insertRow(i_w_trakcie);
                ui->oznacz->setEnabled(true);
                ui->tab_w_trakcie->setItem(i_w_trakcie,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,5,new QTableWidgetItem(query.value(5).toString()));
                i_w_trakcie++;
            }
            else
            {
                ui->tab_zrealizowane->insertRow(i_zrealizowane);
                ui->tab_zrealizowane->setItem(i_zrealizowane,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,5,new QTableWidgetItem(query.value(5).toString()));
                i_zrealizowane++;
            }
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

void Zamowienia_pracownik::on_oznacz_clicked()
{
    QString data_ = QDate::currentDate().toString("MM-dd-yyyy");
    int idx = ui->tab_w_trakcie->currentRow();
    QString zamowienie_ = ui->tab_w_trakcie->item(idx,0)->text();

    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Oznacz jako zrealizowane",
                                   "Jesteś pewien, że chcesz zmienić status zamównienia na zrealizowany?",
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        QSqlQuery query(db);
//        qDebug()<<"UPDATE zamowienie SET data_wyslania = '" + data_ + "' WHERE id_zamowienie = " + zamowienie_;
        if(query.exec("UPDATE zamowienie SET data_wyslania = '" + data_ + "' WHERE id_zamowienie = " + zamowienie_))
        {
            QMessageBox::information(this, "Oznacz jako zrealizowane", "Zamówienie zostało oznaczone jako zrealizowane!");
            ui->tab_w_trakcie->setRowCount(0);
            ui->tab_zrealizowane->setRowCount(0);
            zamowienia();

            if(ui->tab_w_trakcie->rowCount() == 0)
                ui->oznacz->setDisabled(true);
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
}

void Zamowienia_pracownik::on_szczegoly_clicked()
{
    zpi = new Zamowienie_pracownik_info(this);
    zpi->show();
}
