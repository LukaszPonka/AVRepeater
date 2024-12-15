# :wrench: Opis części hardware

## :hammer: Budowa
Urządzenie składa się części interfejsowej, części sterującej oraz gniazda zasilania.

Na interfejs składają się:
- przyciski `S1` do `S4` do wprowadzania sekwencji gracza 1
- przyciski `S5` do `S8` do wprowadzania sekwencji gracza 2
- przycisk `S10` do zatwierdzenia wprowadzonej sekwencji
- diodę `LED1` czerwoną sygnalizującą niepoprawne wprowadzenie sekwencji
- diodę `LED2` zieloną sygnalizującą poprawne wprowadzenie sekwencji

Część sterująca składa się głównie z mikrokontrolera AVR Atmega 328P-PU w obudowie typu DIP, który jest sercem urządzenia, oraz z elementów pasywnych służących do jego działania: kondensatory filtrujące, rezonator kwarcowy 16kHz; a także przycisku do resetowania mikrokontrolera

Zasilanie urządzenia 5V DC poprzez wbudowane gniazdo USB typ A

Schemat elektryczny urządzenia znajdziemy w pliku [PDF](./schemav2.pdf)

### :office: Płytka PCB
Płytka PCB (jednostronna) zaprojektowana została specjalnie na potrzeby urządzenia. 

Wymiary płytki 58,5mm x 69,5mm
Widok płytki PCB z lokalizacją poszególnych elementów znajdziemy w pliku [PDF](./board_view_v2.pdf)

### :battery: Elementy
Listę elementów użytych w urządzeniu znajdziemy w pliku [PDF](./bom.xls)


## 🛠️ Produkcja
Pliki Gerber do produkcji płytki PCB przygotowane pod konfigurację firmy JLCPCB znajdują się w folderze [Gerber_JLCPCB](./Gerber_JLCPCB).
