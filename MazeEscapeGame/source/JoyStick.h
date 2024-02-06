// JoyStick.h
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

extern "C" {
#include "peripherals.h"
#include "pin_mux.h"
#include "board.h"

}

class JoyStick {
public:
    JoyStick();
    virtual ~JoyStick();

    void initialize(); // Dodaj tę metodę, aby inicjalizować ustawienia JoySticka

    void ADC_IRQ_Handler();

    uint16_t getJoyAxisX() const;
    uint16_t getJoyAxisY() const;
    bool isReady() const;
    void setReady(bool ready);
    bool isJoySw() const;

private:
    lpadc_conv_result_t g_LpadcResultConfigStruct;
    volatile uint16_t joyAxisX = 0, joyAxisY = 0;
    volatile bool joySw = false;
    volatile bool ready = false;
};



#endif /* JOYSTICK_H_ */
