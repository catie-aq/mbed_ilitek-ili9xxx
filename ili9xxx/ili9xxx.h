/*
 * Copyright (c) 2020, CATIE
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CATIE_SIXTRON_ILI9XXX_H_
#define CATIE_SIXTRON_ILI9XXX_H_

#include "mbed.h"

namespace sixtron {

//ILI9XXX registers
#define CMD_NOP     	0x00
#define CMD_SWRESET 	0x01
#define CMD_SLPIN   	0x10
#define CMD_SLPOUT  	0x11
#define CMD_PTLON   	0x12
#define CMD_NORML   	0x13
#define CMD_DISPON  	0x29
#define CMD_CLMADRS   	0x2A
#define CMD_PGEADRS   	0x2B
#define CMD_RAMWR   	0x2C
#define CMD_PIXFMT  	0x3A

class ILI9XXX
{
public:
    ILI9XXX(SPI *spi, PinName cs, PinName dcx, PinName backlight);
    void exit_sleep();
    void write_command(uint8_t cmd);
    void write_data(uint8_t data, int len = 1);
    void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void clearScreen(uint16_t color);
    void displayImage(uint16_t *image, uint16_t width, uint16_t height);
    void write_data_16(uint16_t *data, int t);
    virtual void init();

private:
    SPI *_spi;
    DigitalOut _cs;
    DigitalOut _dcx;
    PwmOut _backlight;

};

} // namespace sixtron

#endif // CATIE_SIXTRON_ILI9XXX_H_

