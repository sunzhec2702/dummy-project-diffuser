#ifndef __BLE_DIFFUSER_PERIPHERIAL_CALLBACKS_H
#define __BLE_DIFFUSER_PERIPHERIAL_CALLBACKS_H
#include "ble_diffuser_peripherial_service.h"

extern void ble_rgb_led_write_handler (ble_diffuser_t * p_diffuser, uint8_t length, uint8_t * new_value);
extern void ble_main_button_write_handler (ble_diffuser_t * p_diffuser, uint8_t new_value);
extern void ble_fan_write_handler (ble_diffuser_t * p_diffuser, uint8_t new_value);

#endif



