/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#ifndef TwoWire_h
#define TwoWire_h

#include "stm32_def.h"
#include <inttypes.h>
#include "Stream.h"
#include "util/toolschain.h"  /*for __deprecated(x)*/
#if __has_include("configs/i2cEepromConfig.h")
#  include "configs/i2cEepromConfig.h"
#endif

#define BUFFER_LENGTH 32

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1
#define MASTER_ADDRESS  0x33

/*
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,   //!< Peripheral is not yet Initialized        
  HAL_I2C_STATE_READY             = 0x20U,   //!< Peripheral Initialized and ready for use
  HAL_I2C_STATE_BUSY              = 0x24U,   //!< An internal process is ongoing            
  HAL_I2C_STATE_BUSY_TX           = 0x21U,   //!< Data Transmission process is ongoing      
  HAL_I2C_STATE_BUSY_RX           = 0x22U,   //!< Data Reception process is ongoing         
  HAL_I2C_STATE_LISTEN            = 0x28U,   //!< Address Listen Mode is ongoing            
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   //!< Address Listen Mode and Data Transmission
                                             //    process is ongoing                         
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   //!< Address Listen Mode and Data Reception
                                             //  process is ongoing                         
  HAL_I2C_STATE_ABORT             = 0x60U,   //!< Abort user request ongoing                
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,   //!< Timeout state                             
  HAL_I2C_STATE_ERROR             = 0xE0U    //!< Error                                    

}HAL_I2C_StateTypeDef;
*/

typedef enum 
{
  WIRE_OK        = 0x00U, //HAL_OK / HAL_I2C_STATE_RESET
  WIRE_ERROR     = 0x01U, //HAL_ERROR
  WIRE_BUSY      = 0x02U, //HAL_BUSY
  WIRE_TIMEOUT   = 0x03U, //HAL_TIMEOUT
  
  WIRE_UNINIT    = 0x10U,  
  WIRE_NO_HANDLE = 0x11U,
  
  WIRE_STATE_READY             = 0x20U,   //!< Peripheral Initialized and ready for use
  WIRE_STATE_BUSY              = 0x24U,   //!< An internal process is ongoing            
  WIRE_STATE_BUSY_TX           = 0x21U,   //!< Data Transmission process is ongoing      
  WIRE_STATE_BUSY_RX           = 0x22U,   //!< Data Reception process is ongoing         
  WIRE_STATE_LISTEN            = 0x28U,   //!< Address Listen Mode is ongoing            
  WIRE_STATE_BUSY_TX_LISTEN    = 0x29U,   //!< Address Listen Mode and Data Transmission process is ongoing  
  WIRE_STATE_BUSY_RX_LISTEN    = 0x2AU,   //!< Address Listen Mode and Data Reception process is ongoing 
  WIRE_STATE_ABORT             = 0x60U,   //!< Abort user request ongoing                
  WIRE_STATE_TIMEOUT           = 0xA0U,   //!< Timeout state                             
  WIRE_STATE_ERROR             = 0xE0U    //!< Error                                    
  
} WIRE_StatusTypeDef;

typedef struct {
	WIRE_StatusTypeDef status;
    I2C_HandleTypeDef handle;
    uint8_t sda;
	uint8_t scl;
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    uint8_t isMaster,transmitting;
    uint8_t address;

    uint8_t slaveBuffer;
} TWOWIRE_TypeDef;

class TwoWire : public Stream {
  public:
/*    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    uint8_t isMaster,transmitting;
    uint8_t address;

    uint8_t slaveBuffer;
//    GPIO_TypeDef *sdaPort = NULL;
    uint8_t sda = 0;
//    GPIO_TypeDef *sclPort = NULL;
    uint8_t scl = 0;
*/

    void (*user_onRequest)(void) = NULL;
    void (*user_onReceive)(int) = NULL;
    void onRequestService(void);
    void onReceiveService(uint8_t*, int);




	TwoWire(){}; //add huaweiwx@sina.com 2017.8.2
    TwoWire(uint8_t,uint8_t); //add huaweiwx@sina.com 2017.8.2
    TwoWire(I2C_TypeDef *instance);
    TwoWire(I2C_TypeDef *instance, uint8_t sda, uint8_t scl){
		    pdev->handle.Instance = instance;
            pdev->sda = sda;
            pdev->scl = scl;
			};
    WIRE_StatusTypeDef setPins(uint8_t sda,uint8_t scl);
	
    void begin();
    void begin(uint8_t);
    void begin(int);
    void end();
	
    void setClock(uint32_t);
	
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );

    void stm32SetInstance(I2C_TypeDef *instance){pdev->handle.Instance = instance;};

    __deprecated("have a new func instead: setPins(sdapin,sclpin) add by huaweiwx")
    void stm32SetSDA(uint8_t sda){pdev->sda = sda;};
  
	__deprecated("have a new func instead: setPins(sdapin,sclpin) add by huaweiwx")
    void stm32SetSCL(uint8_t scl){pdev->scl = scl;};

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
	
	TWOWIRE_TypeDef *pdev = &sdev;	
 private:
	TWOWIRE_TypeDef sdev;
/*	= {
		.status = WIRE_OK,
		.sda = 0xff,
		.scl = 0xff,
	};
	*/
};

extern TwoWire Wire;

#endif
