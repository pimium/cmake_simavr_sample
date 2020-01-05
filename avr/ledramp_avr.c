
#include <avr/interrupt.h>
#include <avr/io.h>
//#include <avr/sleep.h>
//
// for linker, emulator, and programmer's sake
#include "avr_mcu_section.h"

#ifndef MCU
#define MCU "atmega168"
#endif

AVR_MCU(F_CPU, MCU);

volatile uint8_t tickCount;

ISR(TIM0_COMPA_vect) // handler for Output Compare 1 overflow interrupt
{
  tickCount++;
}

void tick_init() {
  TCCR0A = (1 << WGM01);
  // use CLK/8 prescale value, clear timer/counter on compareA match
  TCCR0B = (1 << CS00) | (0 << CS01) | (1 << CS02);

  OCR0A = 200;
  TIMSK0 |= (1 << OCIE0A);
}

volatile uint8_t pressed = 0;

ISR(PCINT0_vect) {
  pressed = (PINB & (1 << PB3)) ? 0 : 1;
}

int main() {
  DDRB = 0xf7; // all PORT B output

  //	// enable pin change interrupt for PORT C pin 0
  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << PCINT3); // C0

  tick_init();
  sei();

  // uint8_t mask = 0;

  while (1) {

    if (pressed)
      PORTB = 0x07;
    else
      PORTB = (1 << (tickCount & 0x03));
  }
}
