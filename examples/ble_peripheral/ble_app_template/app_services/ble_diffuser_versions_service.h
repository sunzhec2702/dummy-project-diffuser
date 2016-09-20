#ifndef __BLE_DIFFUSER_VERSIONS_H
#define __BLE_DIFFUSER_VERSIONS_H
#include "ble_gatts.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "ble_srv_common.h"

// Forward declaration of the ble_bas_t type.
typedef struct ble_versions_s ble_versions_t;

/**@brief Battery Service event handler type. */
typedef void (*ble_versions_evt_handler_t) (ble_versions_t * p_version);

/**@brief Battery Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_versions_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Battery Service. */
} ble_versions_init_t;

/**@brief Battery Service structure. This contains various status information for the service. */
struct ble_versions_s
{
    uint16_t                      service_handle;                 /**< Handle of Battery Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      software_version_handles;          /**< Handles related to the Battery Level characteristic. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
};

extern uint32_t ble_diffuser_versions_init(ble_versions_t * p_versions, const ble_versions_init_t * p_verions_init);
extern void ble_versions_on_ble_evt(ble_versions_t * p_versions, ble_evt_t * p_ble_evt);

#endif





