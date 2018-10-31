#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN         PB4
#define DELAY_MAX       (512)
#define DELAY_MIN       (1)

#if DELAY_MAX < 1 || DELAY_MIN < 1
# warning "Value of DELAY_MAX and DELAY_MAIN should be from range <1, 2^16>"
#endif
#if !(DELAY_MAX > DELAY_MIN)
# warning "Value of DELAY_MAX should be greater then DELAY_MIN"
#endif

int
main(void)
{
        uint16_t delay = DELAY_MIN;
        uint8_t dir = 0;

        /* setup */
        DDRB = 0b00000001; // set LED pin as OUTPUT
        PORTB = 0b00000001; // set LED pin to HIGH

        /* loop */
        while (1) {

                PORTB &= ~(_BV(LED_PIN)); // LED off
                _delay_loop_2(delay);

                PORTB |= _BV(LED_PIN); // LED on
                _delay_loop_2(DELAY_MAX - delay);

                if (dir) { // fade-in
                        if (++delay >= (DELAY_MAX - 1)) dir = 0;
                } else { // fade-out
                        if (--delay <= DELAY_MIN) dir = 1;
                }

        }
}
