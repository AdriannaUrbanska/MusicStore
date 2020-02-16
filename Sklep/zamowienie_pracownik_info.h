#ifndef ZAMOWIENIE_PRACOWNIK_INFO_H
#define ZAMOWIENIE_PRACOWNIK_INFO_H

#include <QDialog>

namespace Ui {
class Zamowienie_pracownik_info;
}
/**
 *  Klasa Zamowienie_pracownik_info okna szczegółowych informacji o zamówieniu dla pracownika
 */
class Zamowienie_pracownik_info : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienie_pracownik_info(QWidget *parent = 0);
    ~Zamowienie_pracownik_info();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda aktualizująca pola informacji o zamówieniu
     */
    void info();

private:
    Ui::Zamowienie_pracownik_info *ui;
};

#endif // ZAMOWIENIE_PRACOWNIK_INFO_H
