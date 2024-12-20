# 🚀 Opis części Programowej 


## 🛠️ Kompilacja
Pliki do kompilacji znajdują się w folderze [Compiler](./Compiler).

Aby skompilować program:
1. Przejdź do pliku [Compiler/readme.md](./Compiler/readme.md).
2. Postępuj zgodnie z zawartymi tam instrukcjami dotyczącymi konfiguracji kompilatora oraz wymaganych bibliotek.


## 🔍 Podgląd i edycja kodu
Główny kod programu znajduje się w pliku [Compiler/main.c](./Compiler/main.c).


## 📚 Wykorzystane biblioteki

- **`<avr/io.h>`**: Obsługa rejestrów mikrokontrolera.
- **`<util/delay.h>`**: Obsługa funkcji opóźnienia (`_delay_ms`).
- **`<stdbool.h>`**: Definicje logicznych wartości `true` i `false`.


## 🔑 Kluczowe funkcje programu

### 📌 Definiowanie portów
- **Diody LED**:
  - 🟢 Zielona: `PB4`
  - 🔴 Czerwona: `PB5`
- **Przyciski**:
  - Gracz 1: `PD0`, `PD1`, `PD2`, `PD3`
  - Gracz 2: `PC2`, `PC3`, `PC4`, `PC5`
  - Start gry: `PB0`

### ⚙️ Funkcje użytkowe
1. **Inicjalizacja UART** (`uart_init`)  
   Konfiguracja komunikacji szeregowej z wybraną szybkością transmisji.
2. **Wysyłanie tekstu przez UART** (`uart_print`)  
   Umożliwia przesyłanie komunikatów w czasie rzeczywistym.
3. **Sprawdzenie wciśnięcia przycisku** (`button_pressed`)  
   Obsługuje wykrywanie wciśnięcia przycisków z eliminacją drgań styków (debouncing).
4. **Miganie diodą** (`blink`)  
   Proste miganie wybraną diodą LED.



## 🔄 Główna pętla programu

Główna funkcja programu (`main`) obsługuje:
- Inicjalizację portów i urządzeń.
- Oczekiwanie na wciśnięcie przycisku startu.
- Przełączanie między turami graczy.
- Restart gry po zakończeniu rozgrywki.



## ℹ️ Ważne informacje dla użytkownika

1. **Pull-up dla przycisków**  
   Wszystkie przyciski mają włączony rezystor podciągający, dzięki czemu nie wymagają dodatkowych komponentów.

2. **Komunikaty UART**  
   - Poprawne oraz błędne działania graczy są raportowane w konsoli UART.

3. **Maksymalna długość sekwencji**  
   Program obsługuje maksymalnie **10** przycisków w jednej turze. 

   Możesz dostosować tę wartość w kodzie programu: `#define MAX_SEQ 10`
   

## ⚠️ Uwagi i porady
- W razie problemów z kompilacją upewnij się, że biblioteki AVR są poprawnie skonfigurowane w kompilatorze.
- Kod można dostosować do innych portów mikrokontrolera poprzez edycję definicji portów i pinów.