#include <stdint.h>

// ISR(TIM0_COMPA_vect)
#define ISR(wert) void ISR##wert(void)

#ifndef main
#define main main_
#endif

uint8_t TCCR0A;
uint8_t TCCR0B;
uint8_t TIMSK0;
uint8_t GIMSK;
uint8_t PCMSK;
uint8_t OCR0A;

uint8_t PORTB;
uint8_t PINB;
uint8_t DDRB;

const uint8_t PB3 = 3;

const uint8_t CS00 = 0;
const uint8_t CS01 = 1;
const uint8_t CS02 = 2;

const uint8_t PCINT3 = 3;

const uint8_t WGM01 = 1;
const uint8_t OCIE0A = 0;
const uint8_t PCIE = 0;

void sei(void){}