#ifndef OCENA_H
#define OCENA_H

#include <QDialog>

namespace Ui {
class Ocena;
}
/**
 *  Klasa Ocena okna dodawania oceny do zamówionego produktu
 */
class Ocena : public QDialog
{
    Q_OBJECT

public:
    explicit Ocena(QWidget *parent = 0);
    ~Ocena();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Dodaj ocenę
     */
    void on_dodaj_clicked();

    /**
     * Metoda aktualizująca pola do wypełnienia
     */
    void ustaw();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Usuń ocenę'
     */
    void on_usun_clicked();

private:
    Ui::Ocena *ui;
};

#endif // OCENA_H
