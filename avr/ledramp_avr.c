
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
//
// for linker, emulator, and programmer's sake
#include "avr_mcu_section.h"

#ifndef MCU
#define MCU attiny13
#endif

AVR_MCU(F_CPU, MCU);

#include <stdio.h>
/* ------------------------------------------------------------------------- */
static int uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

volatile uint8_t rotate_counter = 0;
volatile uint8_t tickCount;
volatile uint8_t state = 0;

ISR(TIMER2_COMPA_vect) // handler for Output Compare 1 overflow interrupt
{
  sei();
  tickCount++;
}

ISR(INT0_vect) {
  if ((PIND & (1 << PD3))) {
    rotate_counter++;
  } else {
    rotate_counter--;
  }
  state = 1;
}

void initEncoder(void) {
  DDRD &= ~((1 << PD2) | (1 << PD3));
  EIMSK = 1 << INT0;                   // Enable INT0
  EICRA = (1 << ISC01) | (1 << ISC00); // Trigger INT0 on rising edge
}

void tick_init() {
  /*
          Timer 2 as RTC
   */
  // needs to do that before changing the timer registers
  // ASYNC timer using a 32k crystal
  ASSR |= (1 << AS2);
  TCCR2A = (1 << WGM21);
  // use CLK/8 prescale value, clear timer/counter on compareA match
  TCCR2B = (1 << CS20) | (1 << CS21);
  /*   -- MathPad
                 clock=32768
                 prescaler=8
                 hz=64
                 (clock/prescaler/hz)-1:63 -- */
  OCR2A = 127;
  TIMSK2 |= (1 << OCIE2A);
}

volatile uint8_t pressed = 0;

ISR(PCINT1_vect) {
  if ((PINC & (1 << PC0)) == 1)
    pressed++;
  // wouldn't do that on real hardware, but it's a demo...
  printf("PCINT1_vect %02x\n", PINC);
}

int main() {
  DDRB = 0xff; // all PORT B output
  DDRC = 0;    // make PORT C input
  // enable pin change interrupt for PORT C pin 0
  PCMSK1 |= (1 << PCINT8); // C0
  PCICR |= (1 << PCIE1);

  stdout = &mystdout;

  tick_init();
  sei();

  uint8_t mask = 0;
  for (;;) {

    if (state) {
      state = 0;
      mask = 0xff;
    }

    if (pressed) {
      mask <<= 1;
      pressed = 0;
      if (!mask)
        mask = 0x1;
      PORTB = mask;
    }

    sleep_mode();
  }
}
