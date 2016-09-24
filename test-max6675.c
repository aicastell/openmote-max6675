/**
 * \addtogroup openmote-examples
 * @{
 *
 * \defgroup openmote-max6675
 *
 *    This example tests the correct functionality of the MAX6675
 *    temperature sensor using the SPI bus on the Openmote platform
 *
 * @{
 *
 * \file
 *          Testing the MAX6675 sensor on the OpenMote-CC2538 platform.
 * \author
 *         Angel Ivan Castell Rovira <al004140@gmail.com>
 */

#include "contiki.h"
#include "dev/max6675.h"
#include "dev/leds.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(sensor_max6675_test, "Sensor MAX6675");
AUTOSTART_PROCESSES(&sensor_max6675_test);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(sensor_max6675_test, ev, data)
{
    static struct etimer period_timer;
    static uint16_t temperature;
    static uint8_t msb;
    static uint8_t lsb;
    static uint8_t state;

    PROCESS_BEGIN();
    PROCESS_PAUSE();

    leds_on(LEDS_ALL);

    printf("Starting...\n");

    max6675_initialize();
    etimer_set(&period_timer, (2*CLOCK_SECOND));

    while(1)
    {
        PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_TIMER);

        leds_toggle(LEDS_ALL);

        temperature = max6675_read();

        state = (temperature & 0x0004) >> 2;
        msb = (temperature & 0xFF00) >> 8;
        lsb = (temperature & 0xFF);
        temperature = (temperature >> 3);
        temperature = (temperature & 0x0FFF);

        printf("MSB = 0x%x, LSB = 0x%x, state = 0x%x, temperature = %dºC\n\n",
                msb, lsb, state, temperature/4);

        etimer_restart(&period_timer);
    }

    PROCESS_END();
}

