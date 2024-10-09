#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

// ################################################
//               DEFINIOWANIE PORTÓW
// ################################################

// Definicja wyjść
#define LED_GREEN PB2       // Zielona dioda
#define LED_RED PB3         // Czerwona dioda
#define LED_PLAYER1 PB4     // Dioda gracza 1
#define LED_PLAYER2 PB5     // Dioda gracza 2

// Definicja wejść - przyciski gracza 1 i gracza 2
#define BTN1_P1 PD2
#define BTN2_P1 PD3
#define BTN3_P1 PD4
#define BTN4_P1 PD5

#define BTN1_P2 PD6
#define BTN2_P2 PD7
#define BTN3_P2 PB0
#define BTN4_P2 PB1

// ################################################
//               DEFINIOWANIE ZMIENNYCH
// ################################################

#define MAX_SEQ 20   // Maksymalna długość sekwencji
#define PLAYER_SWITCH_TIME 2000  // Przełączanie gracza po 2 sekundy
#define PLAYER_LOSE_TIME 5000     // Czas przegranej 5 sekund

uint8_t sequence[MAX_SEQ];   // Sekwencja gracza 1
uint8_t seq_length = 0;      // Długość sekwencji
bool player1_turn;    // Który gracz jest aktywny (początkowo gracz 1)
bool game_started = false;

// ################################################
//               INICJALIZACJA UART
// ################################################

// Funkcja inicjalizacji UART
void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);  // Wyższy bajt
    UBRR0L = (unsigned char)ubrr;         // Niższy bajt
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8-bit dane
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);    // Włączenie odbiornika i nadajnika
}

// Funkcja wysyłająca ciąg znaków (string) przez UART
void uart_print(const char *str) {
    while (*str) {
        while (!(UCSR0A & (1 << UDRE0)));  // Czekaj, aż bufor transmisji będzie pusty
        UDR0 = *str++;                     // Wyślij znak
    }
}

// Funkcje zmieniające aktywnego gracza
void player1() {
    PORTB &= ~(1 << LED_PLAYER2);   // Wyłączenie diody gracza 2
    PORTB |= (1 << LED_PLAYER1);    // Włączenie diody gracza 1
    player1_turn = true;
}

void player2() {
    PORTB &= ~(1 << LED_PLAYER1);   // Wyłączenie diody gracza 1
    PORTB |= (1 << LED_PLAYER2);    // Włączenie diody gracza 2
    player1_turn = false;
}

// Funkcja kończąca grę
void end_game() {
    PORTB &= ~(1 << LED_PLAYER1);   // Wyłączenie diody gracza 1
    PORTB &= ~(1 << LED_PLAYER2);   // Wyłączenie diody gracza 2
}

// Funkcja mrugająca diodą
void blink_led(uint8_t led) {
    PORTB |= (1 << led);   // Zapalenie diody
    _delay_ms(200);        // Opóźnienie 200 ms
    PORTB &= ~(1 << led);  // Zgaszenie diody
}

// Sprawdzenie, czy przycisk został wciśnięty
bool button_pressed(volatile uint8_t *port, uint8_t pin) {
    if (!(*port & (1 << pin))) {  // Sprawdzanie czy przycisk jest naciśnięty (niski stan)
        _delay_ms(10);            // Debouncing
        while (!(*port & (1 << pin)));  // Czekaj, aż przycisk zostanie puszczony
        return true;
    }
    return false;
}

// Funkcja rejestrująca ruchy gracza
void register_moves() {
    uint32_t last_press_time = 0; // Czas ostatniego naciśnięcia
    seq_length = 0;                // Resetowanie długości sekwencji

    while (seq_length < MAX_SEQ) {
        // Sprawdzanie naciśnięć przycisków dla gracza 1
        if (player1_turn) {

          /*if (button_pressed(&PIND, BTN1_P1)) {
            sequence[seq_length++] = BTN1_P1;
            blink_led(LED_PLAYER1); // Mrugnięcie diodą
            last_press_time = 0; // Resetuj czas ostatniego naciśnięcia
           } else if (button_pressed(&PIND, BTN1_P1)) {
            sequence[seq_length++] = BTN2_P1;
            blink_led(LED_PLAYER1); // Mrugnięcie diodą
            last_press_time = 0; // Resetuj czas ostatniego naciśnięcia
          } else if (button_pressed(&PIND, BTN3_P1)) {
            sequence[seq_length++] = BTN3_P1;
            blink_led(LED_PLAYER1); // Mrugnięcie diodą
            last_press_time = 0; // Resetuj czas ostatniego naciśnięcia
          } else if (button_pressed(&PIND, BTN4_P1)) {
            sequence[seq_length++] = BTN4_P1;
            blink_led(LED_PLAYER1); // Mrugnięcie diodą
            last_press_time = 0; // Resetuj czas ostatniego naciśnięcia
          } else {
            last_press_time++;
          }

          if (last_press_time >= PLAYER_SWITCH_TIME) {
            uart_print("Czas na zmianę gracza!\r\n");
            player2(); // Zmiana gracza
            break; // Przerywamy rejestrowanie ruchów
          }*/


          last_press_time =+ 1;
          if (last_press_time >= PLAYER_SWITCH_TIME) {
            uart_print("Czas na zmianę gracza!\r\n");
          }

        }

        
    }
}

int main(void) {
    // Inicjalizacja UART
    uart_init(9600);  
    
    // Konfiguracja portów dla diod
    DDRB |= (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_PLAYER1) | (1 << LED_PLAYER2);
    
    // Konfiguracja portów dla przycisków
    DDRD &= ~((1 << BTN1_P1) | (1 << BTN2_P1) | (1 << BTN3_P1) | (1 << BTN4_P1) | (1 << BTN1_P2) | (1 << BTN2_P2));
    DDRB &= ~((1 << BTN3_P2) | (1 << BTN4_P2));

    // Konfiguracja Pull-up dla przycisków 
    PORTD |= (1 << BTN1_P1) | (1 << BTN2_P1) | (1 << BTN3_P1) | (1 << BTN4_P1) | (1 << BTN1_P2) | (1 << BTN2_P2);
    PORTB |= (1 << BTN3_P2) | (1 << BTN4_P2);  

    uart_print("Oczekiwanie na pierwszy ruch.......\r\n");

    while (1) {
        // Oczekiwanie na pierwsze naciśnięcie
        if (!game_started) {
            end_game();
            if (button_pressed(&PIND, BTN1_P1) || button_pressed(&PIND, BTN2_P1) || 
                button_pressed(&PIND, BTN3_P1) || button_pressed(&PIND, BTN4_P1)) 
            {
                game_started = true;
                player1();
                uart_print("Zaczyna gracz 1!\r\n");
                register_moves(); // Rozpoczęcie rejestracji ruchów gracza 1
            } 
            else if (button_pressed(&PIND, BTN1_P2) || button_pressed(&PIND, BTN2_P2) || 
                     button_pressed(&PINB, BTN3_P2) || button_pressed(&PINB, BTN4_P2)) 
            {
                game_started = true;
                player2();
                uart_print("Zaczyna gracz 2!\r\n");
                register_moves(); // Rozpoczęcie rejestracji ruchów gracza 2
            }
        }
        
        // Można dodać dodatkową logikę do przetwarzania gry po zakończeniu rejestracji ruchów
    }
}
