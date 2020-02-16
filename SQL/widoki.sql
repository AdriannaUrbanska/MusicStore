CREATE VIEW
    uzytkownicy_K AS
    SELECT k.login login_, d.haslo haslo_ FROM sklep.klient k JOIN sklep.dane d using(id_dane);

CREATE VIEW
    uzytkownicy_P AS
	SELECT p.login_pracownik, d.haslo FROM sklep.pracownik p JOIN sklep.dane d using(id_dane);

CREATE VIEW
	produkty AS
	SELECT p.nazwa_produktu n, k.nazwa k_n, p.opis_produktu, p.cena_produktu, p.dostepna_liczba_sztuk FROM sklep.produkt p JOIN sklep.kategoria k USING(id_kategoria);

CREATE VIEW
	id_dane_next AS
	SELECT id_dane + 1 FROM sklep.dane ORDER BY id_dane DESC LIMIT 1;

CREATE VIEW
	id_adres_next AS
	SELECT id_adres + 1 FROM sklep.adres ORDER BY id_adres DESC LIMIT 1;

CREATE VIEW
	id_zamowienie_next AS
	SELECT id_zamowienie + 1 FROM sklep.zamowienie ORDER BY id_zamowienie DESC LIMIT 1;



