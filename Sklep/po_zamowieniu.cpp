#include "po_zamowieniu.h"
#include "ui_po_zamowieniu.h"
#include "moje_zamowienia.h"

Po_zamowieniu::Po_zamowieniu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Po_zamowieniu)
{
    ui->setupUi(this);
}

Po_zamowieniu::~Po_zamowieniu()
{
    delete ui;
}

void Po_zamowieniu::on_powrot_clicked()
{
    this->close();
    this->parentWidget()->close();
    this->parentWidget()->parentWidget()->close();
}

void Po_zamowieniu::on_m_zamowienia_clicked()
{
    this->close();
    this->parentWidget()->close();
    this->parentWidget()->parentWidget()->close();

    Moje_zamowienia * m = new Moje_zamowienia(this->parentWidget()->parentWidget()->parentWidget());
    m->show();
}
