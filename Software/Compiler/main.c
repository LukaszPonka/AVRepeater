#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

// ################################################
//               DEFINIOWANIE PORTÓW
// ################################################

// Definicja wyjść
#define LED_GREEN PB2
#define LED_RED PB3

// Definicja wejść
#define BTN1_P1 PD2
#define BTN2_P1 PD3
#define BTN3_P1 PD4
#define BTN4_P1 PD5

#define BTN1_P2 PD6
#define BTN2_P2 PD7
#define BTN3_P2 PB0
#define BTN4_P2 PB1

// Definicja wejść - przycisk start
#define BNT_START PB4

// ################################################
//               DEFINIOWANIE ZMIENNYCH
// ################################################

#define MAX_SEQ 10            // Maksymalna długość sekwencji
#define PLAYER_LOSE_TIME 5000 // Czas przegranej 5 sekund

uint8_t sequence[MAX_SEQ]; // Sekwencja gracza 1
uint8_t seq_length = 0;    // Długość sekwencji
bool player1_turn;         // Który gracz jest aktywny (początkowo gracz 1)
bool game_started = false; // Kontrola stanu gry

// ################################################
//               INICJALIZACJA UART
// ################################################

// Funkcja inicjalizacji UART
void uart_init(unsigned int baud)
{
  unsigned int ubrr = F_CPU / 16 / baud - 1;
  UBRR0H = (unsigned char)(ubrr >> 8);    // Wyższy bajt
  UBRR0L = (unsigned char)ubrr;           // Niższy bajt
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit dane
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Włączenie odbiornika i nadajnika
}

// Funkcja wysyłająca ciąg znaków (string) przez UART
void uart_print(const char *str)
{
  while (*str)
  {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = *str++; // Wyślij znak
  }
}

// ################################################
//                      FUNKCJE
// ################################################

// Sprawdzenie, czy przycisk został wciśnięty
bool button_pressed(volatile uint8_t *port, uint8_t pin)
{
  if (!(*port & (1 << pin))) // Sprawdzanie czy przycisk jest naciśnięty (niski stan)
  {                
    _delay_ms(10); // Debouncing
    while (!(*port & (1 << pin))); // Czekaj, aż przycisk zostanie puszczony
    return true;
  }
  return false;
}

// Funkcja do migania diodą
void blink(uint8_t led)
{
  PORTB |= (1 << led);  // Włączenie diody
  _delay_ms(100);       // Opóźnienie 100 ms
  PORTB &= ~(1 << led); // Wyłączenie diody
}

// Sygnalizacja wygranej
void signal_success() {
    uart_print("Gracz 2 wygrał!\r\n");
    PORTB |= (1 << LED_GREEN);  // Zapalenie zielonej diody, która pozostanie włączona do restartu
}

// Sygnalizacja przegranej
void signal_failure() {
    uart_print("Gracz 2 przegrał!\r\n");
    PORTB |= (1 << LED_RED);  // Zapalenie czerwonej diody, która pozostanie włączona do restartu
}

// Funkcja dla gracza 1 do wprowadzania sekwencji
void player1()
{
  seq_length = 0; // Zerowanie długości sekwencji

  while (seq_length < MAX_SEQ)
  {
    // Sprawdzanie naciśnięć przycisków dla gracza 1
    if (button_pressed(&PIND, BTN1_P1))
    {
      sequence[seq_length++] = BTN1_P1;
      uart_print("BNT1\n");
      blink(LED_GREEN); // Miganie zieloną diodą po naciśnięciu
    }
    else if (button_pressed(&PIND, BTN2_P1))
    {
      sequence[seq_length++] = BTN2_P1;
      uart_print("BNT2\n");
      blink(LED_GREEN); // Miganie zieloną diodą po naciśnięciu
    }
    else if (button_pressed(&PIND, BTN3_P1))
    {
      sequence[seq_length++] = BTN3_P1;
      uart_print("BNT3\n");
      blink(LED_GREEN); // Miganie zieloną diodą po naciśnięciu
    }
    else if (button_pressed(&PIND, BTN4_P1))
    {
      sequence[seq_length++] = BTN4_P1;
      uart_print("BNT4\n");
      blink(LED_GREEN); // Miganie zieloną diodą po naciśnięciu
    }
    else if (button_pressed(&PINB, BNT_START))
    {
      break; // Zakończ wprowadzanie sekwencji
    }
  }
}

// Funkcja dla gracza 2 do odtwarzania sekwencji
void player2()
{
  uint8_t input_seq_length = 0; // Indeks dla porównywania sekwencji gracza 1

  uart_print("Gracz 2: Odtwórz sekwencję!\r\n");
  // Gracz 2 odtwarza sekwencję
  while (input_seq_length < seq_length)
  {
    // Sprawdzenie wciśniętego przycisku przez gracza 2
        blink(LED_GREEN); // Miganie zieloną diodą przy poprawnym wciśnięciu
        input_seq_length++;
      }
      else
      {
        uart_print("Źle!\r\n");
        signal_failure();
        return; // Gracz 2 przegrał, wyjście z funkcji
      }
    }
    else if (button_pressed(&PIND, BTN2_P2))
    {
      if (sequence[input_seq_length] == BTN2_P1)
      {
        uart_print("Dobrze!\r\n");
        blink(LED_GREEN); // Miganie zieloną diodą przy poprawnym wciśnięciu
        input_seq_length++;
      }
      else
      {
        uart_print("Źle!\r\n");
        signal_failure();
        return; // Gracz 2 przegrał, wyjście z funkcji
      }
    }
    else if (button_pressed(&PINB, BTN3_P2))
    {
      if (sequence[input_seq_length] == BTN3_P1)
      {
        uart_print("Dobrze!\r\n");
        blink(LED_GREEN); // Miganie zieloną diodą przy poprawnym wciśnięciu
        input_seq_length++;
      }
      else
      {
        uart_print("Źle!\r\n");
        signal_failure();
        return; // Gracz 2 przegrał, wyjście z funkcji
      }
    }
    else if (button_pressed(&PINB, BTN4_P2))
    {
      if (sequence[input_seq_length] == BTN4_P1)
      {
        uart_print("Dobrze!\r\n");
        blink(LED_GREEN); // Miganie zieloną diodą przy poprawnym wciśnięciu
        input_seq_length++;
      }
      else
      {
        uart_print("Źle!\r\n");
        signal_failure();
        return; // Gracz 2 przegrał, wyjście z funkcji
      }
    }
  }

  // Jeśli gracz 2 poprawnie odtworzył całą sekwencję
  signal_success();
}

// Sygnalizacja wygranej
void signal_success()
{
  uart_print("Gracz 2 wygrał!\r\n");
  PORTB |= (1 << LED_GREEN); // Zapalenie zielonej diody, która pozostanie włączona do restartu
}

// Sygnalizacja przegranej
void signal_failure()
{
  uart_print("Gracz 2 przegrał!\r\n");
  PORTB |= (1 << LED_RED); // Zapalenie czerwonej diody, która pozostanie włączona do restartu
}

// Główna pętla programu
int main(void)
{
  // Inicjalizacja UART
  uart_init(9600);

  // Konfiguracja portów dla diod
  DDRB |= (1 << LED_RED) | (1 << LED_GREEN);

  // Konfiguracja portów dla przycisków
  DDRD &= ~((1 << BTN1_P1) | (1 << BTN2_P1) | (1 << BTN3_P1) | (1 << BTN4_P1) | (1 << BTN1_P2) | (1 << BTN2_P2));
  DDRB &= ~((1 << BTN3_P2) | (1 << BTN4_P2) | (1 << BNT_START));

  // Konfiguracja Pull-up dla przycisków
  PORTD |= (1 << BTN1_P1) | (1 << BTN2_P1) | (1 << BTN3_P1) | (1 << BTN4_P1) | (1 << BTN1_P2) | (1 << BTN2_P2);
  PORTB |= (1 << BTN3_P2) | (1 << BTN4_P2) | (1 << BNT_START);

  uart_print("Oczekiwanie na pierwszy ruch.......\r\n");

  while (1)
  {
    // Oczekiwanie na pierwsze naciśnięcie
    if (!game_started)
    {
      if (button_pressed(&PINB, BNT_START))
      {
        player1_turn = true;
        game_started = true;
        uart_print("Gra rozpoczęta!\r\n");
        PORTB &= ~(1 << LED_RED) & ~(1 << LED_GREEN);
      }
    }
    else
    {
      if (player1_turn)
      {
        uart_print("Gracz 1: Wybierz sekwencję!\r\n");
        player1();

        player1_turn = false; // Przełączenie tury na gracza 2
        blink(LED_GREEN);
        blink(LED_RED);
        blink(LED_GREEN);
        blink(LED_RED);
      }
      else
      {
        player2();
        game_started = false; // Restartowanie gry po zakończeniu
      }
    }
  }
}