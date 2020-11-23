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

#include "ili9xxx/ili9xxx.h"

namespace sixtron {

#define SIZE 20480

ILI9XXX::ILI9XXX(SPI *spi, PinName cs, PinName dcx, PinName backlight):_spi(spi), _cs(cs),_dcx(dcx),_backlight(backlight)
{
    _backlight.period_ms(1);
	_backlight.write(0.3f);
}

void ILI9XXX::init(){
        
}

void ILI9XXX::exit_sleep()
{
	write_command(CMD_SLPOUT);
	ThisThread::sleep_for(120ms);
}

void ILI9XXX::write_command(uint8_t cmd)
{
	// Write command
	_dcx = 0;
	_cs = 0;
    _spi->write(cmd);
	_cs = 1;
}

void ILI9XXX::write_data(uint8_t data, int len)
{
	// Write Data 8 bits
	_spi->format(8);
	_dcx = 1;
	_cs = 0;
	for(int i=0; i<len; i++){
	    _spi->write(data);
		data++;
	}
	_cs = 1;
}

void ILI9XXX::write_data_16(uint16_t* data, int t)
{
	// Write Data 16 bits
	_spi->format(16);
	_dcx = 1;
	_cs = 0;
	for(int i=0; i<t; i++){
	    _spi->write(*data);
		data++;
	}
	_cs = 1;
}

void ILI9XXX::setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
	write_command(CMD_CLMADRS);
	write_data_16(&x0,1);
	write_data_16(&x1,1);

	write_command(CMD_PGEADRS);
	write_data_16(&y0,1);
	write_data_16(&y1,1);

	write_command(CMD_RAMWR);
}

void ILI9XXX::displayImage(uint16_t *image, uint16_t width, uint16_t height){
	uint8_t x0 = (128-width)/2;
	uint8_t x1 = (128-width)/2;
	uint8_t y0 = x0 + width -1;
	uint8_t y1 = x1 + height -1;
	setAddr(x0,x1,y0,y1);
	write_data_16(image, width*height);
}

void ILI9XXX::clearScreen(uint16_t color){
	int px;
	uint16_t table[SIZE];
	setAddr(0,0,128,160);
	
	for (px = 0; px < SIZE; px++){
		table[px] = color;
	}

	write_data_16(table, SIZE);
}

} // namespace sixtron

