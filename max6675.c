/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. Neither the name of the Universitaet Karlsruhe (TH) nor the names
 *    of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author(s): Angel Ivan Castell Rovira <al004140@gmail.com>
 */

#include "max6675.h"
#include "board.h"
#include "spi-arch.h"
#include "dev/spi.h"

#define SPI_SET_CS() \
    GPIO_SET_PIN(GPIO_PORT_TO_BASE(SPI_SEL_PORT), GPIO_PIN_MASK(SPI_SEL_PIN))

#define SPI_CLR_CS() \
    GPIO_CLR_PIN(GPIO_PORT_TO_BASE(SPI_SEL_PORT), GPIO_PIN_MASK(SPI_SEL_PIN))

void
max6675_initialize()
{
    spi_cs_init(SPI_SEL_PORT, SPI_SEL_PIN);
    spi_init();
    spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 16); /* 16 data bits */
}

uint16_t
max6675_read()
{
    uint16_t rawdata;

    /* Enable SSI0 CLK */
    spi_enable();

    SPI_CLR_CS();
    SPI_READ(rawdata);
    SPI_SET_CS();

    /* Gate SSI0 CLK, save power! */
    spi_disable();

    return rawdata;
}

