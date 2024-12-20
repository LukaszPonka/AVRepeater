
# 🎮 Gra - AVREPEATER

  

## :triangular_flag_on_post: Wstęp

Gra polega na wprowadzeniu przez gracza nr 1 sekwencji przycisków, którą gracz nr 2 musi odtworzyć w poprawnej kolejności. Dopuszczalne są kombinacje maksymalnie dziesięciokrokowe. Jeśli gracz 2 zrobi to poprawnie, wygrywa, w przeciwnym razie przegrywa.


## 🚀 Wersja demonstracyjna online
Symulator programu dostępny tutaj: [👉 Demo](https://wokwi.com/projects/411113571342260225)


## :round_pushpin: Sterowanie:

- **Gracz 1:** używa czterech przycisków przypisanych do portów `PD0`, `PD1`, `PD2`, `PD3`.

- **Gracz 2:** używa czterech przycisków przypisanych do portów `PC2`, `PC3`, `PC4`, `PC5`.

- **Start gry lub zakończenie wprowadzania sekwencji:** wciśnięcie przycisku przypisanego do portu `PB0`.


  

## :mega: Zasady:

1. Gracz 1 wprowadza sekwencję do 10 przycisków.

   - Zielona dioda miga po zarejestrowaniu naciśnięcia.

2. Gracz 2 odtwarza tę sekwencję, naciskając odpowiednie przyciski.

	- Zielona dioda miga, jeśli przycisk został poprawnie odtworzony.

3. Diody migają naprzemiennie, informując o zakończeniu tury gracza 1.

	- Koniec tury nastąpić może po osiągnięciu maksymalnej ilości kombinacji (10).

	- Lub po naciśnięciu przycisku START.

4. Po każdej próbie odtworzenia:

	- Zielona dioda zapala się, jeśli sekwencja została odtworzona poprawnie.

	- Czerwona dioda zapala się, jeśli sekwencja została odtworzona błędnie.



## :checkered_flag: Koniec gry:

- Gracz 2 wygrywa, jeśli poprawnie odtworzy całą sekwencję.

- Gracz 2 przegrywa, jeśli popełni błąd.

- Po zakończeniu gry dioda pozostaje włączona, a gra restartuje się po wciśnięciu przycisku START.


## :ticket: Dokumentacja:

- Schemat układu [PDF](./Hardware/schemav2.pdf)

- Lista materiałowa [XLS](./Hardware/bom.xls)

- Board view [PDF](./Hardware/board_view_v2.pdf)

- Pliki produkcyjne Gerber dla JLCPCB [Gerber](./Hardware/gerber%20for%20jlcpcb/)
  
- Kod programu [main.c](./Software/Compiler/main.c)

- Dokumentacja części softwerowej [README.md](./Software/README.md)
