//TODO I2C slave mode for chips that use something else than I2C_IT_BUF

#include <Arduino.h>
#include "Wire.h"
#include "stm32_gpio_af.h"

#if defined(STM32F0)||defined(STM32L0)  /*F0/L0*/
#define I2C1_EV_IRQn I2C1_IRQn
#define I2C2_EV_IRQn I2C1_IRQn
#endif

/** TwoWire object used when in slave interrupt
 */
#if defined(I2C4)
# define I2C_PORT_NR 4
#elif defined(I2C3)
# define I2C_PORT_NR 3
#elif defined(I2C2)
# define I2C_PORT_NR 2
#else
# define I2C_PORT_NR 1
#endif

TwoWire *slaveTwoWire[I2C_PORT_NR];


TwoWire::TwoWire(I2C_TypeDef *instance) {
    pdev->handle.Instance = instance;
}

TwoWire::TwoWire(uint8_t sda,uint8_t scl) { //add huaweiwx@sina.com 2017.8.2
    this->setPins(sda,scl);
}

WIRE_StatusTypeDef TwoWire::setPins(uint8_t _sda,uint8_t _scl) {
    pdev->sda = _sda;
    pdev->scl = _scl;
    pdev->handle.Instance = stm32GetI2CInstance(variant_pin_list[_sda].port,
	                                      variant_pin_list[_sda].pinMask,
										  variant_pin_list[_scl].port,
										  variant_pin_list[_scl].pinMask);
	if(pdev->handle.Instance) return WIRE_OK;
	return WIRE_ERROR;
}

void TwoWire::begin(void){
    if(pdev->status !=WIRE_OK) return;  //
    pdev->rxBufferIndex = 0;
    pdev->rxBufferLength = 0;

    pdev->txBufferIndex = 0;
    pdev->txBufferLength = 0;

    pdev->isMaster = 1;


#if defined(I2C1) && (USE_I2C1)
    if (pdev->handle.Instance == I2C1) {
        __HAL_RCC_I2C1_CLK_ENABLE();
    }
#endif
#if defined(I2C2) && (USE_I2C2)
    if (pdev->handle.Instance == I2C2) {
        __HAL_RCC_I2C2_CLK_ENABLE();
    }
#endif
#if defined(I2C3) && (USE_I2C3)
    if (pdev->handle.Instance == I2C3) {
        __HAL_RCC_I2C3_CLK_ENABLE();
    }
#endif
#if defined(I2C4) && (USE_I2C4)
    if (pdev->handle.Instance == I2C4) {
        __HAL_RCC_I2C4_CLK_ENABLE();
    }
#endif
	
    stm32AfI2CInit(pdev->handle.Instance,
				   variant_pin_list[pdev->sda].port,
	               variant_pin_list[pdev->sda].pinMask,
				   variant_pin_list[pdev->scl].port,
				   variant_pin_list[pdev->scl].pinMask);

    pdev->handle.Init.OwnAddress1 = 0;
    pdev->handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    pdev->handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    pdev->handle.Init.OwnAddress2 = 0;
    pdev->handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    pdev->handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    setClock(100000);
}

void TwoWire::begin(uint8_t address) {
    pdev->rxBufferIndex = 0;
    pdev->rxBufferLength = 0;

    pdev->txBufferIndex = 0;
    pdev->txBufferLength = 0;

    pdev->isMaster = 0;
	
    pdev->address = address << 1;


#if defined(I2C1) && (USE_I2C1)
    if (pdev->handle.Instance == I2C1) {
        slaveTwoWire[0] = this;
        __HAL_RCC_I2C1_CLK_ENABLE();
        HAL_NVIC_SetPriority(I2C1_EV_IRQn, I2C_PRIORITY, 0);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    }
#endif
#if defined(I2C2) && (USE_I2C2)
    if (pdev->handle.Instance == I2C2) {
        slaveTwoWire[1] = this;
        __HAL_RCC_I2C2_CLK_ENABLE();
        HAL_NVIC_SetPriority(I2C2_EV_IRQn, I2C_PRIORITY, 0);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
    }
#endif
#if defined(I2C3) && (USE_I2C3)
    if (pdev->handle.Instance == I2C3) {
        slaveTwoWire[2] = this;
        __HAL_RCC_I2C3_CLK_ENABLE();
        HAL_NVIC_SetPriority(I2C3_EV_IRQn, I2C_PRIORITY, 0);
        HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
    }
#endif
#if defined(I2C4) && (USE_I2C4)
    if (pdev->handle.Instance == I2C4) {
        slaveTwoWire[3] = this;
        __HAL_RCC_I2C4_CLK_ENABLE();
        HAL_NVIC_SetPriority(I2C4_EV_IRQn, I2C_PRIORITY, 0);
        HAL_NVIC_EnableIRQ(I2C4_EV_IRQn);
    }
#endif

    stm32AfI2CInit (pdev->handle.Instance, 
					variant_pin_list[pdev->sda].port,
	                variant_pin_list[pdev->sda].pinMask,
					variant_pin_list[pdev->scl].port,
					variant_pin_list[pdev->scl].pinMask);
									
    pdev->handle.Init.OwnAddress1 = pdev->address;
    pdev->handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    pdev->handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    pdev->handle.Init.OwnAddress2 = 0;
    pdev->handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    pdev->handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    setClock(100000);
    HAL_I2C_Slave_Receive_IT(&pdev->handle, &pdev->slaveBuffer, 1);

    //TODO rewrite IRQ handling to not use HAL_I2C_EV_IRQHandler, so F1 can also work L0?
#if !(defined(STM32F1)||defined(STM32L0))
     HAL_I2C_EnableListen_IT(&pdev->handle);
#endif
}

void TwoWire::begin(int address) {
   begin((uint8_t)address);
}

void TwoWire::end(void) {
  HAL_I2C_DeInit(&pdev->handle);
}

void TwoWire::setClock(uint32_t frequency) {

#if defined(STM32F1) || defined(STM32F2) || defined(STM32F4) || defined(STM32L1)
        pdev->handle.Init.ClockSpeed = frequency;
        pdev->handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
#else
        UNUSED(frequency);
        // I2C1_100KHZ_TIMING needs to be #defined in variant.h for these boards
        // Open STM32CubeMX, select your chip, clock configuration according to systemclock_config.c
        // Enable all I2Cs, go to I2Cx configuration, parameter settings, copy the Timing value.
#if defined(I2C1) && (USE_I2C1)
            if (pdev->handle.Instance == I2C1) pdev->handle.Init.Timing = I2C1_100KHZ_TIMING;
#endif
#if defined(I2C2) && (USE_I2C2)
            if (pdev->handle.Instance == I2C2) pdev->handle.Init.Timing = I2C2_100KHZ_TIMING;
#endif
#if defined(I2C3) && (USE_I2C3)
            if (pdev->handle.Instance == I2C3) pdev->handle.Init.Timing = I2C3_100KHZ_TIMING;
#endif
#if defined(I2C4) && (USE_I2C4)
            if (pdev->handle.Instance == I2C4) pdev->handle.Init.Timing = I2C4_100KHZ_TIMING;
#endif

#endif

    HAL_I2C_Init(&pdev->handle);
}


uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t __attribute__ ((unused)) sendStop) {
  if (pdev->isMaster == true) {
    if (isize > 0) {
		// send internal address; this mode allows sending a repeated start to access
		// some devices' internal registers. This function is executed by the hardware
		// TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)
		
		beginTransmission(address);
		
		// the maximum size of internal address is 3 bytes
		if (isize > 3){
			isize = 3;
		}
		
		// write internal register address - most significant byte first
		while (isize-- > 0){
		   write((uint8_t)(iaddress >> (isize*8)));
		}
		endTransmission(false);
    }

    // clamp to buffer length
    if(quantity > BUFFER_LENGTH){
		quantity = BUFFER_LENGTH;
    }

    // perform blocking read into buffer
    //uint8_t read = twi_readFrom(address, rxBuffer, quantity, sendStop);
    uint8_t read = 0;

    if (HAL_I2C_Master_Receive(&pdev->handle, address << 1, pdev->rxBuffer, quantity, 1000) == HAL_OK) {
        read = quantity;
    }

    // set rx buffer iterator vars
    pdev->rxBufferIndex = 0;
    pdev->rxBufferLength = read;

    return read;
  }

  return 0;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address) {
	pdev->transmitting = 1;
    // set address of targeted slave
    pdev->txAddress = address << 1;
    // reset tx buffer iterator vars
    pdev->txBufferIndex = 0;
    pdev->txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

//
//  Originally, 'endTransmission' was an f(void) function.
//  It has been modified to take one parameter indicating
//  whether or not a STOP should be performed on the bus.
//  Calling endTransmission(false) allows a sketch to
//  perform a repeated start.
//
//  WARNING: Nothing in the library keeps track of whether
//  the bus tenure has been properly ended with a STOP. It
//  is very possible to leave the bus in a hung state if
//  no call to endTransmission(true) is made. Some I2C
//  devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t __attribute__ ((unused)) sendStop) {
    int8_t ret = 0;

    if (pdev->isMaster == true) {
        HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&pdev->handle, 
		             pdev->txAddress, pdev->txBuffer, pdev->txBufferLength, HAL_MAX_DELAY);
        switch(status) {
            case HAL_OK :
                ret = 0;
                break;
            case HAL_TIMEOUT :
                ret = 1;
                break;
            default:
                ret = 4;
                break;
        }

        pdev->txBufferIndex = 0;
        pdev->txBufferLength = 0;
		pdev->transmitting = 0;
    }

    return ret;
}

//  This provides backwards compatibility with the original
//  definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void) {
    return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data) {
    if(pdev->isMaster) {
        // in master transmitter mode
        // don't bother if buffer is full
        if(pdev->txBufferLength >= BUFFER_LENGTH){
              setWriteError();
              return 0;
        }
        // put byte in tx buffer
       pdev->txBuffer[pdev->txBufferIndex] = data;
        ++pdev->txBufferIndex;
        // update amount in buffer
        pdev->txBufferLength = pdev->txBufferIndex;
    }else{
        // in slave send mode
        // reply to master

        if (HAL_I2C_Slave_Transmit_IT(&pdev->handle, &data, 1) != HAL_OK) {
            if(pdev->txBufferLength >= BUFFER_LENGTH){
                  setWriteError();
                  return 0;
            }
            // put byte in tx buffer
            pdev->txBuffer[pdev->txBufferIndex] = data;
            ++pdev->txBufferIndex;
            // update amount in buffer
            pdev->txBufferLength = pdev->txBufferIndex;
        }

    }
    return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    if(pdev->isMaster) {
        // in master transmitter mode
        for(size_t i = 0; i < quantity; ++i){
          write(data[i]);
        }
    } else {
        // in slave send mode
        // reply to master
        if (HAL_I2C_Slave_Transmit_IT(&pdev->handle, (uint8_t *)data, quantity) != HAL_OK) {
            for(size_t i = 0; i < quantity; ++i){
              write(data[i]);
            }
        }
    }
    return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void) {
  return pdev->rxBufferLength - pdev->rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void) {
  int value = -1;

  // get each successive byte on each call
  if(pdev->rxBufferIndex < pdev->rxBufferLength){
    value = pdev->rxBuffer[pdev->rxBufferIndex];
    ++pdev->rxBufferIndex;
  }

  return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void) {
  int value = -1;

  if(pdev->rxBufferIndex < pdev->rxBufferLength){
    value = pdev->rxBuffer[pdev->rxBufferIndex];
  }

  return value;
}

void TwoWire::flush(void) {
  pdev->rxBufferIndex = 0;
  pdev->rxBufferLength = 0;
  pdev->txBufferIndex = 0;
  pdev->txBufferLength = 0;

}

TwoWire *interruptWire;

#if defined(I2C1) && (USE_I2C1)
extern "C" void I2C1_EV_IRQHandler(void ) {
    interruptWire = slaveTwoWire[0];
    HAL_I2C_EV_IRQHandler(&interruptWire->pdev->handle);
}
#endif
#if defined(I2C2) && (USE_I2C2)
extern "C" void I2C2_EV_IRQHandler(void ) {
    interruptWire = slaveTwoWire[1];
    HAL_I2C_EV_IRQHandler(&interruptWire->pdev->handle);
}
#endif
#if defined(I2C3) && (USE_I2C3)
extern "C" void I2C3_EV_IRQHandler(void ) {
    interruptWire = slaveTwoWire[2];
    HAL_I2C_EV_IRQHandler(&interruptWire->pdev->handle);
}
#endif
#if defined(I2C4) && (USE_I2C4)
extern "C" void I2C4_EV_IRQHandler(void ) {
    interruptWire = slaveTwoWire[3];
    HAL_I2C_EV_IRQHandler(&interruptWire->pdev->handle);
}
#endif

extern "C" void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef __attribute__ ((unused)) *handle) {
    HAL_I2C_Slave_Receive_IT(&interruptWire->pdev->handle, &interruptWire->pdev->slaveBuffer, 1);

    if (interruptWire != NULL) {
        interruptWire->onReceiveService(&interruptWire->pdev->slaveBuffer, 1);
    }
}

extern "C" void HAL_I2C_AddrCallback(I2C_HandleTypeDef *handle, uint8_t TransferDirection, uint16_t __attribute__ ((unused)) AddrMatchCode) {
    if (interruptWire != NULL && TransferDirection == 0) {
        interruptWire->user_onRequest();

        if (interruptWire->pdev->txBufferLength > 0) {

            handle->pBuffPtr    = interruptWire->pdev->txBuffer;
            handle->XferCount   = interruptWire->pdev->txBufferLength;
            handle->XferSize    = interruptWire->pdev->txBufferLength;

            interruptWire->pdev->txBufferIndex = 0;
            interruptWire->pdev->txBufferLength = 0;

#ifdef I2C_IT_BUF
            __HAL_I2C_ENABLE_IT(handle, I2C_IT_EVT | I2C_IT_BUF);
#endif
        }
    }

}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes) {
  // don't bother if user hasn't registered a callback
  if(!user_onReceive){
    return;
  }

  // don't bother if rx buffer is in use by a master requestFrom() op
  // i know this drops data, but it allows for slight stupidity
  // meaning, they may not have read all the master requestFrom() data yet
  if(pdev->rxBufferIndex < pdev->rxBufferLength){
    return;
  }
  // copy twi rx buffer into local read buffer
  // this enables new reads to happen in parallel
  for(uint8_t i = 0; i < numBytes; ++i){
    pdev->rxBuffer[i] = inBytes[i];
  }
  // set rx iterator vars
  pdev->rxBufferIndex = 0;
  pdev->rxBufferLength = numBytes;
  // alert user program
  user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService() {
  // don't bother if user hasn't registered a callback
  if(!user_onRequest){
    return;
  }

  // reset tx buffer iterator vars
  // !!! this will kill any pending pre-master sendTo() activity
  pdev->txBufferIndex = 0;
  pdev->txBufferLength = 0;
  // alert user program
  user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) ) {
    user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) ) {
    user_onRequest = function;
}


#if defined(SDA) || defined(SCL)
    TwoWire Wire = TwoWire(SDA, SCL);
#else
    TwoWire Wire = TwoWire(I2C1);
#endif

