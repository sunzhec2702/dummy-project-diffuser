#include "ble_diffuser_peripherial_service_callbacks.h"
#include "bsp_btn_ble.h"

void ble_rgb_led_write_handler (ble_diffuser_t * p_diffuser, uint8_t length, uint8_t * new_value)
{
    // change the color of the rgb led according to the new value.
    if (*new_value != 0) {
        LEDS_ON(BSP_LED_1_MASK);
    } else {
        LEDS_OFF(BSP_LED_1_MASK);
    }
}


void ble_main_button_write_handler (ble_diffuser_t * p_diffuser, uint8_t new_value)
{
    // Power Off ? Shut down Fan ? 
    
    
}



void ble_fan_write_handler (ble_diffuser_t * p_diffuser, uint8_t new_value)
{
    // Change the Fan.
    
    
    
}


