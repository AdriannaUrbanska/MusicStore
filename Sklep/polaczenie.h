#ifndef POLACZENIE_H
#define POLACZENIE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Polaczenie;
}

class Polaczenie : public QDialog
{
    Q_OBJECT

public:
    explicit Polaczenie(QWidget *parent = 0);
    ~Polaczenie();

private slots:

    void on_polacz_clicked();

private:
    Ui::Polaczenie *ui;

    MainWindow *w;
};

#endif // POLACZENIE_H
