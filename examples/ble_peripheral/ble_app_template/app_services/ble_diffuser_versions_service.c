#include "ble_diffuser_versions_service.h"
#include "bsp.h"

#define VERSION_LENGTH  3
static uint8_t sw_version[VERSION_LENGTH] = {'0','0','1'};

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_versions       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_versions_t * p_versions, ble_evt_t * p_ble_evt)
{
    p_versions->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_versions       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_versions_t * p_versions, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_versions->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_versions       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
/*
static void on_write(ble_versions_t * p_versions, ble_evt_t * p_ble_evt)
{
    if (p_versions->is_notification_supported) {
        ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

        if ((p_evt_write->handle == p_versions->battery_level_handles.cccd_handle)
            && (p_evt_write->len == 2)) {
            // CCCD written, call application event handler
            if (p_versions->evt_handler != NULL)
            {
                ble_bas_evt_t evt;

                if (ble_srv_is_notification_enabled(p_evt_write->data))
                {
                    evt.evt_type = BLE_BAS_EVT_NOTIFICATION_ENABLED;
                } else {
                    evt.evt_type = BLE_BAS_EVT_NOTIFICATION_DISABLED;
                }

                p_versions->evt_handler(p_versions, &evt);
            }
        }
    }
}
*/

void ble_versions_on_ble_evt(ble_versions_t * p_versions, ble_evt_t * p_ble_evt)
{
    if (p_versions == NULL || p_ble_evt == NULL) {
        return;
    }

    switch (p_ble_evt->header.evt_id) {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_versions, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_versions, p_ble_evt);
            break;
/*
        case BLE_GATTS_EVT_WRITE:
            on_write(p_versions, p_ble_evt);
            break;
*/
        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for adding the Battery Level characteristic.
 *
 * @param[in]   p_versions        Battery Service structure.
 * @param[in]   p_versions_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t software_version_char_add(ble_versions_t * p_versions, const ble_versions_init_t * p_versions_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
//    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
//    uint8_t             init_len;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_SOFTWARE_REVISION_STRING_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);

    attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = VERSION_LENGTH;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = VERSION_LENGTH;
    attr_char_value.p_value   = sw_version;

    err_code = sd_ble_gatts_characteristic_add(p_versions->service_handle, &char_md,
               &attr_char_value,
               &p_versions->software_version_handles);
    if (err_code != NRF_SUCCESS) {
        return err_code;
    }
    return NRF_SUCCESS;
}


uint32_t ble_diffuser_versions_init(ble_versions_t * p_versions, const ble_versions_init_t * p_versions_init)
{
    if (p_versions == NULL || p_versions_init == NULL) {
        return NRF_ERROR_NULL;
    }

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_versions->conn_handle               = BLE_CONN_HANDLE_INVALID;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_DEVICE_INFORMATION_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_versions->service_handle);
    if (err_code != NRF_SUCCESS) {
        return err_code;
    }

    // Add battery level characteristic
    return software_version_char_add(p_versions, p_versions_init);
}


