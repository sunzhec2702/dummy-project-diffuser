#ifndef __BLE_DIFFUSER_PERIPHERIAL_SERVICE_H
#define __BLE_DIFFUSER_PERIPHERIAL_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "ble_srv_common.h"

//FA9Axxxx-3586-49F8-9576-024E4F5E4A85
#define DIFFUSER_UUID_BASE        {0x85, 0x4A, 0x5E, 0x4F, 0x4E, 0x02, 0x76, 0x95, \
                                    0xF8, 0x49, 0x86, 0x35, 0x00, 0x00, 0x9A, 0xFA}
#define DIFFUSER_UUID_SERVICE                0x9527
#define DIFFUSER_UUID_RGB_LED_CHAR           0x9528
#define DIFFUSER_UUID_MAIN_BUTTON_CHAR       0x9529
#define DIFFUSER_UUID_FAN_CHAR               0x952A


typedef struct ble_diffuser_s ble_diffuser_t;
                                   
typedef void (*ble_lbs_rgb_led_write_handler_t) (ble_diffuser_t * p_diffuser, uint8_t length, uint8_t * new_value);
typedef void (*ble_lbs_main_button_write_handler_t) (ble_diffuser_t * p_diffuser, uint8_t new_value);
typedef void (*ble_lbs_fan_write_handler_t) (ble_diffuser_t * p_diffuser, uint8_t new_value);
                        
/**@brief BLE diffuser Service structure. This structure contains various status information for the service. */
struct ble_diffuser_s
{
    uint16_t                    service_handle;      /**< Handle of LED Button Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t    rgb_led_char_handles;    /**< Handles related to the RGB LED Characteristic. */
    ble_gatts_char_handles_t    main_button_char_handles; /**< Handles related to the Main Button Characteristic. */
    ble_gatts_char_handles_t    fan_char_handles;         /** < Handles related to the Fan Characteristic */
    uint8_t                     uuid_type;           /**< UUID type for the LED Button Service. */
    uint16_t                    conn_handle;         /**< Handle of the current connection (as provided by the BLE stack). BLE_CONN_HANDLE_INVALID if not in a connection. */
    ble_lbs_rgb_led_write_handler_t rgb_led_write_handler;   /**< Event handler to be called when the LED Characteristic is written. */
    ble_lbs_main_button_write_handler_t main_button_write_handler;
    ble_lbs_fan_write_handler_t fan_write_handler;
};

/** @brief BLE diffuser Service init structure. This structure contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_lbs_rgb_led_write_handler_t rgb_led_write_handler; /**< Event handler to be called when the LED Characteristic is written. */
    ble_lbs_main_button_write_handler_t main_button_write_handler; /**< Event handler to be called when the main button is written. */
    ble_lbs_fan_write_handler_t fan_write_handler; /**< Event handler to be called when the fan is written. */
} ble_diffuser_init_t;

#define RED_VALUE_MASK          0xFF << 16
#define GREEN_VALUE_MASK        0xFF << 8
#define BLUE_VALUE_MASK         0xFF << 0
#define GET_RED_VALUE(x)        (((x)&RED_VALUE_MASK)>>16)
#define GET_GREEN_VALUE(x)      (((x)&GREEN_VALUE_MASK)>>8)
#define GET_BLUE_VALUE(x)       (((x)&BLUE_VALUE_MASK)>>0)



extern uint32_t ble_diffuser_peripherial_init(ble_diffuser_t * p_diffuser, const ble_diffuser_init_t * p_diffuser_init);
extern void ble_diffuser_on_ble_evt(ble_diffuser_t * p_ble_diffusers, ble_evt_t * p_ble_evt);


//#define BTN_ID_LED0             0  /**< ID of button used to wake up the application. */
//#define BTN_ID_LED1             1  /**< ID of button used to put the application into sleep mode. */
//#define BTN_ID_LED2             2  /**< ID of button used to gracefully terminate a connection on long press. */
//#define BTN_ID_WAKEUP_BOND_DELETE 1  /**< ID of button used to wake up the application and delete all bonding information. */
//#define BTN_ID_WHITELIST_OFF      1  /**< ID of button used to turn off usage of the whitelist. */

//#define BTN_ACTION_SLEEP          BSP_BUTTON_ACTION_RELEASE    /**< Button action used to put the application into sleep mode. */
//#define BTN_ACTION_LED_SWITCH     BSP_BUTTON_ACTION_LONG_PUSH  /**< Button action used to gracefully terminate a connection on long press. */
//#define BTN_ACTION_WHITELIST_OFF  BSP_BUTTON_ACTION_LONG_PUSH  /**< Button action used to turn off usage of the whitelist. */

//extern uint32_t leds_buttons_configure(void);

#endif





