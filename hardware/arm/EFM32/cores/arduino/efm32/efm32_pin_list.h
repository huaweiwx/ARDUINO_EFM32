#ifndef EFM32_PIN_LIST_H
#define EFM32_PIN_LIST_H

#ifdef VARIANT_PIN_LIST
  #define PIN_LIST VARIANT_PIN_LIST
#else
  #define PIN_LIST CHIP_PIN_LIST
#endif

#ifdef __cplusplus

    class __ConstPin {
		public:
			constexpr __ConstPin(const GPIO_Port_TypeDef GPIOx_Port,const  uint32_t pin, const int val)
			                    :GPIOx_Port(GPIOx_Port), pin(pin), val(val) {};
			constexpr operator int() const { return val; }
            const GPIO_Port_TypeDef GPIOx_Port;
			const uint32_t pin;
			const int val;
    };
    #define PIN(a, b) __P##a##b
        enum {
              PIN_LIST
              NUM_DIGITAL_PINS,
        };
    #undef PIN

    #define PIN(a, b) P##a##b(gpioPort ## a,GPIO_PIN_ ## b, __P##a##b)
      constexpr __ConstPin PIN_LIST __IGNORE((GPIO_Port_TypeDef)-1,-1,-1);
    #undef PIN
	
#else

    #define PIN(a, b) P ## a ## b
    enum {
        PIN_LIST
        NUM_DIGITAL_PINS,
    };
    #undef PIN
#endif


#endif
