-------------------------------------------------------------------------------------------------------------------
1. Ocena produktu

CREATE OR REPLACE FUNCTION ocena_produktu(produkt_ VARCHAR)
RETURNS VARCHAR AS
$$
DECLARE
	suma INTEGER;
	ile INTEGER;
	
BEGIN	
	suma := (SELECT SUM(ocena) FROM sklep.ocena_produktu WHERE nazwa_produktu LIKE produkt_ GROUP BY nazwa_produktu);
	ile := (SELECT COUNT(*) FROM sklep.ocena_produktu WHERE nazwa_produktu LIKE produkt_ GROUP BY nazwa_produktu);
	
	IF ile != 0 THEN
		RETURN CAST(CAST(CAST(suma AS DECIMAL(4,2))/ile AS DECIMAL(4,2)) AS VARCHAR);
	ELSIF NOT EXISTS(SELECT nazwa_produktu FROM sklep.produkt WHERE nazwa_produktu LIKE produkt_) THEN
		RETURN 'Taki produkt nie istnieje!';
	ELSE	
		RETURN 'Brak ocen';
	END IF;
END;
$$
LANGUAGE plpgsql;


-------------------------------------------------------------------------------------------------------------------
2. Wyświetlanie swoich zamówień

CREATE OR REPLACE FUNCTION wyszukaj_zamowienia(login_ VARCHAR)
RETURNS TABLE(nazwa VARCHAR, cena DECIMAL(9,2), data_zamowienia DATE, data_wyslania TEXT, id INTEGER) AS
$$
DECLARE
	z RECORD;

BEGIN	
	for z IN (SELECT p.nazwa_produktu n, zm.do_zaplaty c, zm.data_zamowienia d, zm.data_wyslania dw, zm.id_zamowienie i FROM sklep.zamowienie zm JOIN sklep.produkt_zamowienie pz using(id_zamowienie) JOIN sklep.produkt p USING(nazwa_produktu) JOIN sklep.klient k USING(login) WHERE k.login LIKE login_)
		LOOP
			nazwa := z.n;
			cena := z.c;
			data_zamowienia := z.d;
			id := z.i;

			IF z.dw IS NULL THEN
				data_wyslania := 'W trakcie realizacji';
			ELSE
				data_wyslania := 'Wysłane ' || CAST(z.dw AS VARCHAR);
			END IF;

			RETURN NEXT;
		END LOOP;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
3. Nowy użytkownik

--------------------------------Klient
CREATE OR REPLACE FUNCTION poprawnosc_klient()
    RETURNS TRIGGER
    AS $$
    BEGIN
    IF NEW.login IN (SELECT login_ FROM sklep.uzytkownicy_K) THEN
        RAISE EXCEPTION 'Podany login jest już zajęty!';
	ELSIF LENGTH(NEW.login) = 0 THEN
		RAISE EXCEPTION 'Login nie może być pusty!';
    END IF;
  
    RETURN NEW;                                                          
    END;
    $$ LANGUAGE 'plpgsql';


CREATE TRIGGER popr_k_trig
    BEFORE INSERT OR UPDATE ON sklep.klient
    FOR EACH ROW EXECUTE PROCEDURE poprawnosc_klient();


--------------------------------Dane
CREATE OR REPLACE FUNCTION poprawnosc_dane()
    RETURNS TRIGGER
    LANGUAGE plpgsql
    AS $$
    BEGIN

	IF LENGTH(NEW.imie) = 0 OR LENGTH(NEW.nazwisko) = 0 OR LENGTH(NEW.nr_telefonu) = 0 OR LENGTH(NEW.email) = 0 OR LENGTH(NEW.haslo) = 0 THEN
		RAISE EXCEPTION 'Wszystkie pola danych muszą być uzupełnione!';
	ELSIF NEW.email IN (SELECT email FROM sklep.dane) THEN
		RAISE EXCEPTION 'Podany adres email jest już zajęty!';
    END IF;
  
    RETURN NEW;                                                          
    END;
    $$ ;


CREATE TRIGGER popr_d_trig
    BEFORE INSERT OR UPDATE ON sklep.dane
    FOR EACH ROW EXECUTE PROCEDURE poprawnosc_dane();


--------------------------------Adres
CREATE OR REPLACE FUNCTION poprawnosc_adres()
    RETURNS TRIGGER
    LANGUAGE plpgsql
    AS $$
    BEGIN

	IF LENGTH(NEW.ulica) = 0 OR LENGTH(NEW.nr_budynku) = 0 OR LENGTH(NEW.kod_pocztowy) = 0 OR LENGTH(NEW.miasto) = 0 OR LENGTH(NEW.kraj) = 0 THEN
		RAISE EXCEPTION 'Wszystkie obowiązkowe pola adresu muszą być uzupełnione!';
    END IF;
  
    RETURN NEW;                                                          
    END;
    $$;


CREATE TRIGGER popr_a_trig
    BEFORE INSERT OR UPDATE ON sklep.adres
    FOR EACH ROW EXECUTE PROCEDURE poprawnosc_adres();


-------------------------------------------------------------------------------------------------------------------
4. Ile zamówień ma użytkownik

CREATE OR REPLACE FUNCTION ile_zamowien(login_ VARCHAR)
RETURNS text AS
$$
DECLARE
	ile INTEGER;
	
BEGIN	

	SELECT count(*) INTO ile FROM sklep.zamowienie WHERE login LIKE login_;

	return ile;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
5. Wszystkie zamowienia

CREATE OR REPLACE FUNCTION wszystkie_zamowienia()
RETURNS TABLE(id INT, uzytkownik VARCHAR, produkt VARCHAR, sztuki INT, data_zamowienia DATE, data_wyslania TEXT) AS
$$
DECLARE
	z RECORD;
BEGIN	
	for z IN (SELECT zm.id_zamowienie idz, zm.login l, p.nazwa_produktu p, zm.liczba_sztuk sz, zm.data_zamowienia dz, zm.data_wyslania dw FROM sklep.zamowienie zm JOIN sklep.produkt_zamowienie pz using(id_zamowienie) JOIN sklep.produkt p USING(nazwa_produktu) ORDER BY dz)
		LOOP
			id := z.idz;
			uzytkownik := z.l;
			produkt := z.p;
			sztuki := z.sz;
			data_zamowienia := z.dz;

			IF z.dw IS NULL THEN
				data_wyslania := 'W trakcie realizacji';
			ELSE
				data_wyslania := 'Wysłane ' || CAST(z.dw AS VARCHAR);
			END IF;

			RETURN NEXT;
		END LOOP;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
6. Sprawdzanie czy produkt został już oceniony przez użytkownika

CREATE OR REPLACE FUNCTION sprawdz_ocena(login_ VARCHAR, produkt_ VARCHAR)
RETURNS text AS
$$
BEGIN	
	IF EXISTS (SELECT * FROM sklep.ocena_produktu o WHERE (o.nazwa_produktu LIKE produkt_) AND (o.login LIKE login_)) THEN
		RETURN 'TAK';
	ELSE
		RETURN 'NIE';
	END IF;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
7. Usuwanie id_zamowienie z tabeli produkt_zamowienie

CREATE OR REPLACE FUNCTION usun_zamowienie()
    RETURNS TRIGGER
    LANGUAGE plpgsql
    AS $$
    BEGIN
		DELETE FROM sklep.zamowienie WHERE id_zamowienie = OLD.id_zamowienie; 
		RETURN NULL;                                                          
    END;
    $$;


CREATE TRIGGER usun_zam_trig
    AFTER DELETE ON sklep.produkt_zamowienie
    FOR EACH ROW EXECUTE PROCEDURE usun_zamowienie();


-------------------------------------------------------------------------------------------------------------------
8. Pełne informacje o zamówieniu

CREATE TYPE my_type AS (i INTEGER, login VARCHAR, produkt VARCHAR, kategoria VARCHAR, opis VARCHAR, cena DECIMAL(9,2), sztuki INTEGER, przesylka VARCHAR, cena_przesylki DECIMAL(7,2), do_zaplaty DECIMAL(9,2), data_zamowienia DATE, status VARCHAR);

CREATE OR REPLACE FUNCTION wyszukaj_zamowienia(login_ VARCHAR, id_ INTEGER)
RETURNS my_type AS
$$
DECLARE
	zam RECORD;
	rec my_type;
BEGIN	
	for zam IN (SELECT z.id_zamowienie AS a1, z.login AS a2, p.nazwa_produktu AS a3, k.nazwa AS a4, p.opis_produktu AS a5,
			p.cena_produktu AS a6, z.liczba_sztuk AS a7, prz.opcja_dostawy AS a8, prz.cena_dostawy AS a9, 
			z.do_zaplaty AS a10, z.data_zamowienia AS a11, z.data_wyslania AS a12
			FROM sklep.zamowienie z JOIN sklep.produkt_zamowienie USING(id_zamowienie) JOIN sklep.produkt p USING(nazwa_produktu) 
			JOIN sklep.kategoria k USING(id_kategoria) JOIN sklep.przesylka prz USING(id_przesylka) WHERE (login LIKE login_) AND (z.id_zamowienie = id_))
	LOOP

		rec.i := zam.a1;
		rec.login := zam.a2;
		rec.produkt := zam.a3;
		rec.kategoria := zam.a4;
		rec.opis := zam.a5;
		rec.cena := zam.a6;
		rec.sztuki := zam.a7;
		rec.przesylka := zam.a8;
		rec.cena_przesylki := zam.a9;
		rec.do_zaplaty := zam.a10;
		rec.data_zamowienia := zam.a11;
	
		IF zam.a12 IS NULL THEN
			rec.status := 'W trakcie realizacji';
		ELSE
			rec.status := 'Wysłane ' || CAST(zam.a12 AS VARCHAR);
		END IF;

		RETURN rec;
	END LOOP;

END;
$$
LANGUAGE plpgsql;


-------------------------------------------------------------------------------------------------------------------
9. Aktualizacja dostępnej liczby sztuk produktu

CREATE OR REPLACE FUNCTION sztuki(produkt_ VARCHAR, kupione_ INTEGER)
RETURNS text AS
$$
DECLARE
	ile_bylo INTEGER;
BEGIN

	ile_bylo := (SELECT dostepna_liczba_sztuk FROM sklep.produkt WHERE nazwa_produktu LIKE produkt_);

	UPDATE sklep.produkt SET dostepna_liczba_sztuk = ile_bylo - kupione_ WHERE nazwa_produktu LIKE produkt_;
	RETURN 'Zaktualizowane';
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
10. Aktualizacja dostępnej liczby sztuk produktu po anulowaniu zamowienia

CREATE OR REPLACE FUNCTION sztuki_dodaj(produkt_ VARCHAR, kupione_ INTEGER)
RETURNS text AS
$$
DECLARE
	ile_bylo INTEGER;
BEGIN

	ile_bylo := (SELECT dostepna_liczba_sztuk FROM sklep.produkt WHERE nazwa_produktu LIKE produkt_);

	UPDATE sklep.produkt SET dostepna_liczba_sztuk = ile_bylo + kupione_ WHERE nazwa_produktu LIKE produkt_;
	RETURN 'Zaktualizowane';
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
11. Sprawdzanie dostępności loginu

CREATE OR REPLACE FUNCTION login(login_ VARCHAR)
RETURNS text AS
$$
BEGIN
	IF EXISTS (SELECT * FROM sklep.klient WHERE login LIKE login_) THEN
		RETURN 'TAK';
	ELSE
		RETURN 'NIE';
	END IF;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
12. Sprawdzanie dostępności adresu email

CREATE OR REPLACE FUNCTION email(email_ VARCHAR)
RETURNS text AS
$$
BEGIN
	IF EXISTS (SELECT * FROM sklep.dane WHERE email LIKE email_) THEN
		RETURN 'TAK';
	ELSE
		RETURN 'NIE';
	END IF;
END;
$$
LANGUAGE plpgsql;

-------------------------------------------------------------------------------------------------------------------
13. Wszystkie zamówienia w formacie VARCHAR

CREATE OR REPLACE FUNCTION wszystkie_zamowienia_VAR()
RETURNS TABLE(id VARCHAR, uzytkownik VARCHAR, produkt VARCHAR, sztuki VARCHAR, data_zamowienia VARCHAR, data_wyslania VARCHAR) AS
$$
DECLARE
	z RECORD;
BEGIN	
	for z IN (SELECT zm.id_zamowienie idz, zm.login l, p.nazwa_produktu p, zm.liczba_sztuk sz, zm.data_zamowienia dz, zm.data_wyslania dw FROM sklep.zamowienie zm JOIN sklep.produkt_zamowienie pz using(id_zamowienie) JOIN sklep.produkt p USING(nazwa_produktu) ORDER BY dz)
		LOOP
			id := CAST(z.idz AS VARCHAR);
			uzytkownik := CAST(z.l AS VARCHAR);
			produkt := CAST(z.p AS VARCHAR);
			sztuki := CAST(z.sz AS VARCHAR);
			data_zamowienia := CAST(z.dz AS VARCHAR);

			IF z.dw IS NULL THEN
				data_wyslania := 'W trakcie realizacji';
			ELSE
				data_wyslania := 'Wysłane ' || CAST(z.dw AS VARCHAR);
			END IF;

			RETURN NEXT;
		END LOOP;
END;
$$
LANGUAGE plpgsql;


