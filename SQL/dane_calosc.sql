------------------------------------------------------------------------------ADRES
INSERT INTO adres(id_adres, ulica, nr_budynku, nr_mieszkania, miasto, kod_pocztowy, kraj) VALUES
(1, 'Reymonta', '19', '49', 'Kraków', '30-059', 'Polska'),
(2, 'Szewska', '129b', '', 'Kraków', '30-298', 'Polska'),
(3, 'Krakowska', '11', '', 'Wrocław', '50-012', 'Polska'),
(4, 'Basztowa', '239', '4', 'Łódź', '90-021', 'Polska'),
(5, 'Długa', '177c', '82', 'Łódź', '90-821', 'Polska'),
(6, 'Rzemieślnicza', '98', '21', 'Kraków', '30-011', 'Polska'),
(7, 'Lubuska', '4', '8', 'Poznań', '60-123', 'Polska'),
(8, 'Majowa', '455f', '', 'Kraków', '30-011', 'Polska'),
(9, 'Zacisze', '27', '', 'Kraków', '30-765', 'Polska'),
(10, 'Odlewnicza', '76', '', 'Gdańsk', '80-423', 'Polska'),
(11, 'Nawojki', '16', '', 'Kraków', '30-058', 'Polska');

------------------------------------------------------------------------------DANE
INSERT INTO dane VALUES
(1,'Agata', 'Nowak', '+48609283571', 'anowak@gmail.com', 'anowak_haslo'),
(2, 'Daniel', 'Urbaniak', '554372891', 'durbaniak@gmail.com', 'durbaniak_haslo'),
(3, 'Karolina', 'Wierzbkicka', '673892012', 'kwierzbicka@gmail.com', 'kwierzbicka_haslo'),
(4, 'Bartosz', 'Sikorski', '875728176', 'bsikorski@gmail.com', 'bsikorski_haslo'),
(5, 'Krystian', 'Witkowski', '547291094', 'kwitkowski@gmail.com', 'kwitkowski_haslo'),
(6, 'Cezary', 'Grabowski', '788918282', 'cgrabowski@gmail.com', 'cgrabowski_haslo'),
(7, 'Jakub', 'Wróbel', '898637111', 'jwrobel@gmail.com', 'jwrobel_haslo'),
(8, 'Mateusz', 'Szewczyk', '665732543', 'mszewczyk@gmail.com', 'mszewczyk_haslo'),
(9, 'Maria', 'Sokołowska', '601237892', 'msokolowska@gmail.com', 'msokolowska_haslo'),
(10, 'Radosław', 'Szczepaniak', '676832749', 'rszczepaniak@gmail.com', 'rszczepaniak_haslo'),
(11, 'Alicja', 'Górska', '+48875392192', 'agorska@gmail.com', 'agorska_haslo'),
(12, 'Zofia', 'Karpińska', '873912090', 'zkarpinska@gmail.com', 'zkarpinska_haslo'),
(13, 'Justyna', 'Szymańska', '662090828', 'jszymanska@gmail.com', 'jszymanska_haslo'),
(14, 'Kacper', 'Szulc', '576038234', 'kszulc@gmail.com', 'kszulc_haslo'),
(15, 'Nela', 'Dudek', '706293986', 'ndudek@gmail.com', 'ndudek_haslo');

------------------------------------------------------------------------------KATEGORIA
INSERT INTO kategoria VALUES
(1,'Dęte'),
(2, 'Strunowe - smyczkowe'),
(3, 'Strunowe - szarpane'),
(4, 'Klawiszowe'),
(5, 'Perkusyjne');

------------------------------------------------------------------------------KLIENT
INSERT INTO klient VALUES
('cezaryg',2,6),
('jakubw',3,7),
('mateuszs',4,8),
('marias',4,9),
('radoslaws',5,10),
('alicjag',6,11),
('zofiak',7,12),
('justynas',8,13),
('kacpers',9,14),
('nelad',10,15);

------------------------------------------------------------------------------PRACOWNIK
INSERT INTO pracownik VALUES
('agatan', 1, 11),
('danielu', 2, 11),
('karolinaw', 3, 5),
('bartoszs', 4, 9),
('krystianw', 5, 9);

------------------------------------------------------------------------------STANOWISKO
INSERT INTO stanowisko VALUES
(1,'Obsługa klienta', 6000),
(2,'Konserwator', 7000),
(3,'Konsultant', 5000);

------------------------------------------------------------------------------SKLEP_INFO
INSERT INTO sklep_info VALUES
(1,1,'Sklep muzyczny','+48789477442','sklep_muzyczny@gmail.com','Sklep muzyczny sprzedający instrumenty dęte, strunowe-smyczkowe, strunowe-szarpane, perkusyjne oraz klawiszowe.');

------------------------------------------------------------------------------PRACOWNIK_SKLEP
INSERT INTO pracownik_sklep VALUES
(1,'agatan',1),
(1,'danielu',1),
(1,'karolinaw',3),
(1,'bartoszs',1),
(1,'krystianw',2);

------------------------------------------------------------------------------PRODUKT
INSERT INTO produkt(id_kategoria, cena_produktu, nazwa_produktu, opis_produktu, dostepna_liczba_sztuk) VALUES
(1,2906.00,'Flet','Armstrong Flet poprzeczny FL501RE Arioso',15),
(1,3882.00,'Klarnet','Yamaha YCL 450 klarnet Bb',10),
(1,879.00,'Trąbka','JMICHAEL TR 200A trąbka',20),
(1,3722.00,'Saksofon','Conn Saksofon Eb-Alt AS650',8),
(1,3529.00,'Puzon','Bach Puzon tenorowy w stroju Bb/F TB502B',9),
(2,429.00,'Skrzypce akustyczne','Stentor 1018 / C skrzypce Standard 3/4 (futerał + smyczek)',20),
(2,1290.00,'Skrzypce elektryczne','Gewa skrzypce elektryczne 4/4 (brąz)',17),
(2,1032.00,'Altówka','GEWA Altówka z futerałem(komplet) EW 42,0 cm',15),
(2,3107.00,'Wiolonczela','GEWA Wiolonczela z futerałem(komplet) EW 1/4',12),
(2,5529.00,'Kontrabas','GEWA Kontrabas ST 3/4 0 Lity Top',8),
(3,399.00,'Gitara akustyczna','Arrow Bronze NT Natural gitara akustyczna',25),
(3,5619.00,'Gitara basowa','Fender ′50s Precision Bass Lacquer Maple Fingerboard Black gitara basowa',14),
(3,1869.00,'Gitara elektryczna','Blade TM Edition Delta DE-1RC/2TS - gitara elektryczna',20),
(3,1559.00,'Gitara klasyczna','Alhambra 2C gitara klasyczna/top cedr',23),
(3,499.00,'Ukulele','Baton Rouge UR21T ukulele tenorowe',18),
(4,193500.00,'Fortepian','Yamaha C7X PE fortepian (227 cm)',5),
(4,22984.00,'Pianino akustyczne','Yamaha b3 E PE pianino (121 cm)',14),
(4,1499.00,'Keyboard','Casio CT-X3000 instrument klawiszowy',19),
(4,3599.00,'Pianino elektroniczne','Casio AP 270 pianino elektroniczne, czarne',12),
(4,21900.00,'Akordeon','Fisitalia 52.34-FB 52(87)/3/7+3C 120(49)/4(2)/6 akordeon guzikowy z konwertorem (czarny)',7),
(5,8136.00,'Perkusja akustyczna','Ddrum Paladin Walnut Player NB - akustyczny zestaw perkusyjny',17),
(5,2399.00,'Perkusja elektroniczna','Alesis Surge Mesh Kit perkusja elektroniczna',15),
(5,927.00,'Bęben marszowy','GEWA Bęben marszowy Bęben marszowy 14x10″',10),
(5,1052.00,'Mały bęben','GEWA Bęben marszowy Mały bęben 14x5″',10),
(5,8301.00,'Ksylofon','Yamaha YX-135 ksylofon 3 1/2 oktawy f1-c5, płytki: padauk, wys. 87cm',5);

------------------------------------------------------------------------------PRZESYŁKA
INSERT INTO przesylka VALUES
(1,'Odbiór osobisty', 0.00, '0 dni'),
(2,'Przesyłka kurierska',19.00,'5 dni'),
(3,'Przesyłka kurierska pobranie',24.00,'3 dni');

------------------------------------------------------------------------------ZAMÓWIENIE
INSERT INTO zamowienie VALUES
(1,'jakubw',1,1,2906.00,'12-12-2019','14-12-2019'),
(3,'radoslaws',3,1,423.00,'14-12-2019','20-12-2019'),
(4,'mateuszs',1,1,399.00,'25-12-2019','27-12-2019'),
(6,'radoslaws',1,2,2104.00,'26-12-2019','30-12-2019'),
(7,'alicjag',3,1,903.00,'24-12-2019','29-12-2019'),
(8,'zofiak',3,1,3746.00,'02-01-2020','09-01-2020');

INSERT INTO zamowienie(id_zamowienie, login, id_przesylka, liczba_sztuk, do_zaplaty, data_zamowienia) VALUES
(2,'cezaryg',2,1,448.00,'14-01-2020'),
(5,'nelad',2,1,3618.00,'09-01-2020');

------------------------------------------------------------------------------PRODUKT_ZAMOWIENIE
INSERT INTO produkt_zamowienie VALUES
(1,'Flet'),
(2,'Skrzypce akustyczne'),
(3,'Gitara akustyczna'),
(4,'Gitara akustyczna'),
(5,'Pianino elektroniczne'),
(6,'Mały bęben'),
(7,'Trąbka'),
(8,'Saksofon');

------------------------------------------------------------------------------OCENA_PRODUKTU
INSERT INTO ocena_produktu VALUES
('Flet','jakubw', 7, ''),
('Gitara akustyczna','mateuszs',4,'Nie brzmi dobrze.'),
('Mały bęben','radoslaws',2,'Nie warty swojej ceny.'),
('Trąbka','alicjag',8,'Brzmi pięknie!'),
('Saksofon','zofiak',10,'Świetny instrument!'),
('Gitara akustyczna','radoslaws',5,'Spodziewałem się czegoś lepszego...');


