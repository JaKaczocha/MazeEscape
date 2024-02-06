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


    void ADC_IRQ_Handler();

    int getJoyAxisX() const;
    int getJoyAxisY() const;
    bool isReady() const;
    void setReady(bool ready);
    bool isJoySw() const;

private:
    lpadc_conv_result_t g_LpadcResultConfigStruct;
    volatile int joyAxisX = 0, joyAxisY = 0;
    volatile bool joySw = false;
    volatile bool ready = false;
};



#endif /* JOYSTICK_H_ */
