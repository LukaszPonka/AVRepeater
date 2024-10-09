#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>



#define MAX_SEQ 20   // Maksymalna długość sekwencji
#define TIMEOUT_MS 1000  // Limit czasu na naciśnięcie przycisku (1000 ms)


int main(void) {

  // Definicja wyjść
  DDRB |= (1 << 0); // LED_RED
  DDRB |= (1 << 1); // LED_GREEN
  DDRB |= (1 << 2); // BUZZER
  DDRB |= (1 << 3); // LED_PLAYER1
  DDRB |= (1 << 4); // LED_PLAYER2
  
  // Definicja wejść
  DDRD &= ~(1 << 0);
  DDRD &= ~(1 << 1);
  DDRD &= ~(1 << 2);
  DDRD &= ~(1 << 3);
  DDRD &= ~(1 << 4);
  DDRD &= ~(1 << 5);
  DDRD &= ~(1 << 6);
  DDRD &= ~(1 << 7);

  // Pull-up wejść
  PORTD |= (1 << 0);
  PORTD |= (1 << 1);
  PORTD |= (1 << 2);
  PORTD |= (1 << 3);
  PORTD |= (1 << 4);
  PORTD |= (1 << 5);
  PORTD |= (1 << 6);
  PORTD |= (1 << 7);

  while(1) {

    if(!(PIND & (1 << PD0))) {
      PORTB |= (1 << 0);
    } else {
      PORTB &= ~(1 << 0);
    }
  }
}
