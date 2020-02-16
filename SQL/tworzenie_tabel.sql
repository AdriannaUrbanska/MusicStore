CREATE TABLE Kategoria (
                id_kategoria INTEGER NOT NULL,
                nazwa VARCHAR(30) NOT NULL,
                CONSTRAINT id_kategoria PRIMARY KEY (id_kategoria)
);


CREATE TABLE Dane (
                id_dane INTEGER NOT NULL,
                imie VARCHAR(50) NOT NULL,
                nazwisko VARCHAR(50) NOT NULL,
                nr_telefonu VARCHAR(12) NOT NULL,
                email VARCHAR(50) NOT NULL,
                haslo VARCHAR(50) NOT NULL,
                CONSTRAINT id_dane PRIMARY KEY (id_dane),
				UNIQUE (email)
);


CREATE TABLE Stanowisko (
                id_stanowisko INTEGER NOT NULL,
                opis_stanowiska VARCHAR(50) NOT NULL,
                pensja DECIMAL(9,2) NOT NULL,
                CONSTRAINT id_stanowisko PRIMARY KEY (id_stanowisko)
);


CREATE TABLE Przesylka (
                id_przesylka INTEGER NOT NULL,
                opcja_dostawy VARCHAR(50) NOT NULL,
                cena_dostawy DECIMAL(7,2) NOT NULL,
                czas_oczekiwania VARCHAR(50) NOT NULL,
                CONSTRAINT id_przesylka PRIMARY KEY (id_przesylka)
);


CREATE TABLE Adres (
                id_adres INTEGER NOT NULL,
                ulica VARCHAR(50) NOT NULL,
                nr_budynku VARCHAR(7) NOT NULL,
                nr_mieszkania VARCHAR(7),
                kod_pocztowy CHAR(6) NOT NULL,
                miasto VARCHAR(70) NOT NULL,
                kraj VARCHAR(70) NOT NULL,
                CONSTRAINT id_adres PRIMARY KEY (id_adres)
);


CREATE TABLE Klient (
                login VARCHAR(50) NOT NULL,
                id_adres INTEGER NOT NULL,
                id_dane INTEGER NOT NULL,
                CONSTRAINT id_klient PRIMARY KEY (login)
);


CREATE TABLE Zamowienie (
                id_zamowienie INTEGER NOT NULL,
                login VARCHAR(50) NOT NULL,
                id_przesylka INTEGER NOT NULL,
                liczba_sztuk INTEGER NOT NULL,
                do_zaplaty DECIMAL(9,2) NOT NULL,
                data_zamowienia DATE NOT NULL,
                data_wyslania DATE,
                CONSTRAINT id_zamowienie PRIMARY KEY (id_zamowienie)
);


CREATE TABLE Sklep_info (
                id_sklep INTEGER NOT NULL,
                id_adres INTEGER NOT NULL,
                nazwa_sklepu VARCHAR(50) NOT NULL,
                nr_telefonu VARCHAR(12) NOT NULL,
                email VARCHAR(50) NOT NULL,
                opis_sklepu VARCHAR(200) NOT NULL,
                CONSTRAINT id_sklep PRIMARY KEY (id_sklep)
);


CREATE TABLE Pracownik (
                login_pracownik VARCHAR(50) NOT NULL,
                id_dane INTEGER NOT NULL,
                id_adres INTEGER NOT NULL,
                CONSTRAINT id_pracownik PRIMARY KEY (login_pracownik)
);


CREATE TABLE pracownik_sklep (
                id_sklep INTEGER NOT NULL,
                login_pracownik VARCHAR(50) NOT NULL,
                id_stanowisko INTEGER NOT NULL,
                CONSTRAINT id_pracownik_sklep PRIMARY KEY (id_sklep, login_pracownik)
);


CREATE TABLE Produkt (
                nazwa_produktu VARCHAR(50) NOT NULL,
                id_kategoria INTEGER NOT NULL,
                cena_produktu DECIMAL(9,2) NOT NULL,
                opis_produktu VARCHAR(200) NOT NULL,
                dostepna_liczba_sztuk INTEGER NOT NULL,
                CONSTRAINT id_produkt PRIMARY KEY (nazwa_produktu)
);


CREATE TABLE produkt_zamowienie (
                id_zamowienie INTEGER NOT NULL,
                nazwa_produktu VARCHAR(50) NOT NULL,
                CONSTRAINT id_produkt_zamowienie PRIMARY KEY (id_zamowienie, nazwa_produktu)
);


CREATE TABLE Ocena_produktu (
                nazwa_produktu VARCHAR(50) NOT NULL,
                login VARCHAR(50) NOT NULL,
                ocena INTEGER NOT NULL,
                komentarz VARCHAR(200),
                CONSTRAINT id_ocena PRIMARY KEY (nazwa_produktu, login)
);


ALTER TABLE Produkt ADD CONSTRAINT Kategoria_Produkt_fk
FOREIGN KEY (id_kategoria)
REFERENCES Kategoria (id_kategoria)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Klient ADD CONSTRAINT Dane_Klient_fk
FOREIGN KEY (id_dane)
REFERENCES Dane (id_dane)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Pracownik ADD CONSTRAINT Dane_Pracownik_fk
FOREIGN KEY (id_dane)
REFERENCES Dane (id_dane)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE pracownik_sklep ADD CONSTRAINT Stanowisko_pracownik_sklep_fk
FOREIGN KEY (id_stanowisko)
REFERENCES Stanowisko (id_stanowisko)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Zamowienie ADD CONSTRAINT Przesylka_Zamowienie_fk
FOREIGN KEY (id_przesylka)
REFERENCES Przesylka (id_przesylka)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Sklep_info ADD CONSTRAINT Adres_Sklep_info_fk
FOREIGN KEY (id_adres)
REFERENCES Adres (id_adres)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Klient ADD CONSTRAINT Adres_Klient_fk
FOREIGN KEY (id_adres)
REFERENCES Adres (id_adres)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Pracownik ADD CONSTRAINT Adres_Pracownik_fk
FOREIGN KEY (id_adres)
REFERENCES Adres (id_adres)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Ocena_produktu ADD CONSTRAINT Klient_Ocena_produktu_fk
FOREIGN KEY (login)
REFERENCES Klient (login)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Zamowienie ADD CONSTRAINT Klient_Zamowienie_fk
FOREIGN KEY (login)
REFERENCES Klient (login)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE produkt_zamowienie ADD CONSTRAINT Zamowienie_Prod_zamow_fk
FOREIGN KEY (id_zamowienie)
REFERENCES Zamowienie (id_zamowienie)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE pracownik_sklep ADD CONSTRAINT Sklep_info_pracownik_sklep_fk
FOREIGN KEY (id_sklep)
REFERENCES Sklep_info (id_sklep)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE pracownik_sklep ADD CONSTRAINT Pracownik_pracownik_sklep_fk
FOREIGN KEY (login_pracownik)
REFERENCES Pracownik (login_pracownik)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE Ocena_produktu ADD CONSTRAINT Produkt_Ocena_produktu_fk
FOREIGN KEY (nazwa_produktu)
REFERENCES Produkt (nazwa_produktu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;

ALTER TABLE produkt_zamowienie ADD CONSTRAINT Produkt_Prod_zamow_fk
FOREIGN KEY (nazwa_produktu)
REFERENCES Produkt (nazwa_produktu)
ON DELETE NO ACTION
ON UPDATE NO ACTION
NOT DEFERRABLE;
