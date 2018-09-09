/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file Wire.cpp
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief Wire library, uses the WireBase to create the primary interface
 *        while keeping low level interactions invisible to the user.
 */

/*
 * Library updated by crenn to follow new Wire system.
 * Code was derived from the original Wire for maple code by leaflabs and the
 * modifications by gke and ala42.
 */
 /*
  * Updated by Roger Clark. 20141111. Fixed issue when process() returned because of missing ACK (often caused by invalid device address being used), caused SCL to be left
  * LOW so that in the next call to process() , the first clock pulse was not sent, because SCL was LOW when it should have been high.
  */
#include <Arduino.h>
#include "WireSoft.h"

#define I2C_WRITE 0
#define I2C_READ  1

/* low level conventions:
 * - SDA/SCL idle high (expected high)
 * - always start with i2c_delay rather than end
 */

void TwoWireSoft::sclPin(bool state) {
    I2C_DELAY(this->i2c_delay);
    digitalWrite(this->scl_pin,state);
    //Allow for clock stretching - dangerous currently
    if (state == HIGH) {
        while(digitalRead(this->scl_pin) == 0);
    }
}

void TwoWireSoft::sdaPin(bool state) {
	I2C_DELAY(this->i2c_delay);
    digitalWrite(this->sda_pin, state);
}

void TwoWireSoft::i2c_start() {
    sdaPin(LOW);
    sclPin(LOW);
}

void TwoWireSoft::i2c_stop() {
    sdaPin(LOW);
    sclPin(HIGH);
    sdaPin(HIGH);
}

bool TwoWireSoft::i2c_get_ack() {
    sclPin(LOW);
    sdaPin(HIGH);
    sclPin(HIGH);

    bool ret = !digitalRead(this->sda_pin);
    sclPin(LOW);
    return ret;
}

void TwoWireSoft::i2c_send_ack() {
    sdaPin(LOW);
    sclPin(HIGH);
    sclPin(LOW);
}

void TwoWireSoft::i2c_send_nack() {
    sdaPin(HIGH);
    sclPin(HIGH);
    sclPin(LOW);
}

uint8_t TwoWireSoft::i2c_shift_in() {
    uint8_t data = 0;
    sdaPin(HIGH);

    int i;
    for (i = 0; i < 8; i++) {
        sclPin(HIGH);
        data |= digitalRead(this->sda_pin) << (7-i);
        sclPin(LOW);
    }

    return data;
}

void TwoWireSoft::i2c_shift_out(uint8_t val) {
    int i;
    for (i = 0; i < 8; i++) {
        sdaPin(!!(val & (1 << (7 - i)) ) );
        sclPin(HIGH);
        sclPin(LOW);
    }
}

uint8_t TwoWireSoft::process() {
    itc_msg.xferred = 0;

    uint8_t sla_addr = (itc_msg.adr << 1);
    if (itc_msg.flags == I2C_MSG_READ) {
        sla_addr |= I2C_READ;
    }
    i2c_start();
    // shift out the address we're transmitting to
    i2c_shift_out(sla_addr);
    if (!i2c_get_ack()) 
	{
		i2c_stop();// Roger Clark. 20141110 added to set clock high again, as it will be left in a low state otherwise
        return ENACKADDR;
    }
    // Recieving
    if (itc_msg.flags == I2C_MSG_READ) {
        while (itc_msg.xferred < itc_msg.length) {
            itc_msg.data[itc_msg.xferred++] = i2c_shift_in();
            if (itc_msg.xferred < itc_msg.length) 
			{
                i2c_send_ack();
            } 
			else 
			{
                i2c_send_nack();
            }
        }
    }
    // Sending
    else {
        for (uint8_t i = 0; i < itc_msg.length; i++) {
            i2c_shift_out(itc_msg.data[i]);
            if (!i2c_get_ack()) 
			{
				i2c_stop();// Roger Clark. 20141110 added to set clock high again, as it will be left in a low state otherwise
                return ENACKTRNS;
            }
            itc_msg.xferred++;
        }
    }
    i2c_stop();
    return SUCCESS;
}

// TODO: Add in Error Handling if pins is out of range for other Maples
// TODO: Make delays more capable
TwoWireSoft::TwoWireSoft(uint8_t sda, uint8_t scl, uint8_t delay) : i2c_delay(delay) {
    this->scl_pin=scl;
    this->sda_pin=sda;
}

TwoWireSoft::TwoWireSoft() {
#if  defined(SDA)&& defined(SCL)
    this->scl_pin=SCL;
    this->sda_pin=SDA;
#endif
}

void TwoWireSoft::begin(uint8_t self_addr) {
    tx_buf_idx = 0;
    tx_buf_overflow = false;
    rx_buf_idx = 0;
    rx_buf_len = 0;
    pinMode(this->scl_pin, OUTPUT);
    pinMode(this->sda_pin, OUTPUT);
    sclPin(HIGH);
    sdaPin(HIGH);
}

void TwoWireSoft::end()  
{  
	if (this->scl_pin)  
	{  
		pinMode(this->scl_pin, INPUT);  
	}  
	if (this->sda_pin)  
	{  
		pinMode(this->sda_pin, INPUT);  
	}  
}  
 
TwoWireSoft::~TwoWireSoft() {
    this->scl_pin=0xff;
    this->sda_pin=0xff;
}

// Declare the instance that the users of the library can use
TwoWireSoft WireSoft;
//TwoWireSoft WireSoft(PB6, PB7, SOFT_STANDARD);
