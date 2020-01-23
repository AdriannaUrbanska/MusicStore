#ifndef OCENA_H
#define OCENA_H

#include <QDialog>

namespace Ui {
class Ocena;
}

class Ocena : public QDialog
{
    Q_OBJECT

public:
    explicit Ocena(QWidget *parent = 0);
    ~Ocena();

private slots:
    void on_powrot_clicked();

    void on_dodaj_clicked();

    void ustaw();

    void on_usun_clicked();

private:
    Ui::Ocena *ui;
};

#endif // OCENA_H
