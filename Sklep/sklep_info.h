#ifndef SKLEP_INFO_H
#define SKLEP_INFO_H

#include <QDialog>

namespace Ui {
class Sklep_info;
}
/**
 *  Klasa Sklep_info okna informacji o sklepie
 */
class Sklep_info : public QDialog
{
    Q_OBJECT

public:
    explicit Sklep_info(QWidget *parent = 0);
    ~Sklep_info();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda aktualizująca pola informacji o sklepie
     */
    void ustaw();

private:
    Ui::Sklep_info *ui;
};

#endif // SKLEP_INFO_H
