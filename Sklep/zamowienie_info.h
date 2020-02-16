#ifndef ZAMOWIENIE_INFO_H
#define ZAMOWIENIE_INFO_H

#include <QDialog>

namespace Ui {
class Zamowienie_info;
}
/**
 *  Klasa Zamowienie_info okna szczegółowych informacji o zamówieniu dla klienta
 */
class Zamowienie_info : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienie_info(QWidget *parent = 0);
    ~Zamowienie_info();

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
    Ui::Zamowienie_info *ui;
};

#endif // ZAMOWIENIE_INFO_H
