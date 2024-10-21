
# Gra - AVREPEATER

  

## Wstęp

Gra polega na wprowadzeniu przez gracza 1 sekwencji przycisków, którą gracz 2 musi odtworzyć w poprawnej kolejności. Jeśli gracz 2 zrobi to poprawnie, wygrywa, w przeciwnym razie przegrywa.

  

## Sterowanie:

- **Gracz 1:** używa przycisków przypisanych do portów PD2, PD3, PD4, PD5.

- **Gracz 2:** używa przycisków przypisanych do portów PD6, PD7, PB0, PB1.

- **Start gry:** wciśnięcie przycisku przypisanego do portu PB4.

  

## Zasady:

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



## Koniec gry:

- Gracz 2 wygrywa, jeśli poprawnie odtworzy całą sekwencję.

- Gracz 2 przegrywa, jeśli popełni błąd.

- Po zakończeniu gry dioda pozostaje włączona, a gra restartuje się po wciśnięciu przycisku START.