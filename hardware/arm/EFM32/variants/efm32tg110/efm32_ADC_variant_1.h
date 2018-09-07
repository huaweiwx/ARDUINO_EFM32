typedef struct efm32_chip_adc_channel_type
{
  	GPIO_Port_TypeDef GPIOx_Port; 	/* defined in em_gpio.h */
  	uint8_t  Pin_abstraction;	/* emu pin*/    
    unsigned int  adc_channel;
} efm32_chip_adc_channel_type ;

const efm32_chip_adc_channel_type  chip_adc_channel[] = {
    {gpioPortD, GPIO_PIN_4, _ADC_SINGLECTRL_INPUTSEL_CH4},  /* D23/PD4,ADC0_CH4,LEU0_TX #0*/ /**/
    {gpioPortD, GPIO_PIN_5, _ADC_SINGLECTRL_INPUTSEL_CH5},  /* D24/PD5,ADC0_CH5 LEU0_RX #0*/
    {gpioPortD, GPIO_PIN_6, _ADC_SINGLECTRL_INPUTSEL_CH6},  /* D25/PD6,ADC0_CH6 LETIM0_OUT0 #0 I2C0_SDA #1,*/
    {gpioPortD, GPIO_PIN_7, _ADC_SINGLECTRL_INPUTSEL_CH7},  /* D26/PD7,ADC0_CH7 LETIM0_OUT1 #0 I2C0_SCL #1*/
};
