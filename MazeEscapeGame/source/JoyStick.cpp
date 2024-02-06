// JoyStick.cpp
#include <JoyStick.h>


static JoyStick *joyStickInstance = nullptr; // Globalna zmienna wskazująca na instancję JoySticka

JoyStick::JoyStick() {
    // TODO Auto-generated constructor stub
	joyStickInstance = this; // Przypisz wskaźnik na instancję JoySticka
}

JoyStick::~JoyStick() {
    // TODO Auto-generated destructor stub
}



extern "C" {
    void ADC0_IRQHANDLER(void) {
        if (joyStickInstance != nullptr) {
            joyStickInstance->ADC_IRQ_Handler(); // Wywołaj metodę obsługi przerwania na instancji JoySticka
        }
    }
}

int JoyStick::getJoyAxisX() const {
	return this->joyAxisX;
}

int JoyStick::getJoyAxisY() const {
	return this->joyAxisY;
}
bool JoyStick::isReady() const {
	return this->ready;
}
void JoyStick::setReady(bool ready) {
	this->ready = ready;
}
bool JoyStick::isJoySw() const {
	return joySw;
}
void JoyStick::ADC_IRQ_Handler() {
    LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
    joyAxisX = g_LpadcResultConfigStruct.convValue;
    LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
    joyAxisY = g_LpadcResultConfigStruct.convValue;
    joySw = !GPIO_PinRead(BOARD_INITADCPINS_SW_GPIO, BOARD_INITADCPINS_SW_PORT, BOARD_INITADCPINS_SW_PIN);
    ready = true;
}
