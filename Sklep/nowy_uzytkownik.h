#ifndef NOWY_UZYTKOWNIK_H
#define NOWY_UZYTKOWNIK_H

#include <QDialog>
#include "sklep.h"

class Sklep;

namespace Ui {
class Nowy_uzytkownik;
}
/**
 *  Klasa Nowy_uzytkownik okna tworzenia nowego konta klienta
 */
class Nowy_uzytkownik : public QDialog
{
    Q_OBJECT

public:
    explicit Nowy_uzytkownik(QWidget *parent = 0);
    ~Nowy_uzytkownik();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Utwórz konto'
     */
    void on_utworz_konto_clicked();

private:
    Ui::Nowy_uzytkownik *ui;

    Sklep *s;
};

#endif // NOWY_UZYTKOWNIK_H
