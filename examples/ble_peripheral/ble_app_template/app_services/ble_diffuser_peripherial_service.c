#include "ble_diffuser_peripherial_service.h"
#include "string.h"
#include "bsp.h"
#include "ble.h"
#include "ble_gatts.h"

static uint8_t rgb_led_value[3] = {0x01, 0x02, 0x03};
static uint8_t fan_value = 0xFF;
static uint8_t main_button_value = 0xFF;

/**@brief Function for adding the LED Characteristic.
 *
 * @param[in] p_diffuser      RGB LED Button Service structure.
 * @param[in] p_diffuser_init RGB LED Button Service initialization structure.
 *
 * @retval NRF_SUCCESS on success, else an error value from the SoftDevice
 */
static uint32_t rgb_led_char_add(ble_diffuser_t * p_diffuser, const ble_diffuser_init_t * p_diffuser_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;

    ble_uuid.type = p_diffuser->uuid_type;
    ble_uuid.uuid = DIFFUSER_UUID_RGB_LED_CHAR;

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(rgb_led_value)/sizeof(rgb_led_value[0]);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(rgb_led_value)/sizeof(rgb_led_value[0]);
    attr_char_value.p_value      = rgb_led_value;

    return sd_ble_gatts_characteristic_add(p_diffuser->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_diffuser->rgb_led_char_handles);
}


/**@brief Function for adding the Main Button Characteristic.
 *
 * @param[in] p_diffuser      LED Button Service structure.
 * @param[in] p_diffuser_init LED Button Service initialization structure.
 *
 * @retval NRF_SUCCESS on success, else an error value from the SoftDevice
 */
static uint32_t main_button_char_add(ble_diffuser_t * p_diffuser, const ble_diffuser_init_t * p_diffuser_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&cccd_md, 0, sizeof(cccd_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.write  = 1;
    char_md.char_props.read   = 1;
    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;

    ble_uuid.type = p_diffuser->uuid_type;
    ble_uuid.uuid = DIFFUSER_UUID_MAIN_BUTTON_CHAR;

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = &main_button_value;

    return sd_ble_gatts_characteristic_add(p_diffuser->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_diffuser->main_button_char_handles);
}

/**@brief Function for adding the Fan Characteristic.
 *
 * @param[in] p_diffuser      LED Button Service structure.
 * @param[in] p_diffuser_init LED Button Service initialization structure.
 *
 * @retval NRF_SUCCESS on success, else an error value from the SoftDevice
 */
static uint32_t fan_char_add(ble_diffuser_t * p_diffuser, const ble_diffuser_init_t * p_diffuser_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;

    ble_uuid.type = p_diffuser->uuid_type;
    ble_uuid.uuid = DIFFUSER_UUID_FAN_CHAR;

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = 1;
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = 1;
    attr_char_value.p_value      = &fan_value;

    return sd_ble_gatts_characteristic_add(p_diffuser->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_diffuser->fan_char_handles);
}

uint32_t ble_diffuser_peripherial_init(ble_diffuser_t * p_diffuser, const ble_diffuser_init_t * p_diffuser_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure.
    p_diffuser->conn_handle       = BLE_CONN_HANDLE_INVALID;
    p_diffuser->rgb_led_write_handler = p_diffuser_init->rgb_led_write_handler;
    p_diffuser->fan_write_handler = p_diffuser_init->fan_write_handler;
    p_diffuser->main_button_write_handler = p_diffuser_init->main_button_write_handler;

    // Add service.
    ble_uuid128_t base_uuid = {DIFFUSER_UUID_BASE};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_diffuser->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    ble_uuid.type = p_diffuser->uuid_type;
    ble_uuid.uuid = DIFFUSER_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_diffuser->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add characteristics.
    err_code = main_button_char_add(p_diffuser, p_diffuser_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = rgb_led_char_add(p_diffuser, p_diffuser_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = fan_char_add(p_diffuser, p_diffuser_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


static void on_connect(ble_diffuser_t * p_ble_diffusers, ble_evt_t * p_ble_evt)
{
    p_ble_diffusers->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}
static void on_disconnect(ble_diffuser_t * p_ble_diffusers, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_ble_diffusers->conn_handle = BLE_CONN_HANDLE_INVALID;
}
static void on_write(ble_diffuser_t * p_ble_diffusers, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if ((p_evt_write->handle == p_ble_diffusers->rgb_led_char_handles.value_handle) &&
            (p_evt_write->len == 3) &&
            (p_ble_diffusers->rgb_led_write_handler != NULL))
    {
        p_ble_diffusers->rgb_led_write_handler(p_ble_diffusers, p_evt_write->len, p_evt_write->data);
    }

    if ((p_evt_write->handle == p_ble_diffusers->main_button_char_handles.value_handle) &&
            (p_evt_write->len == 1) &&
            (p_ble_diffusers->main_button_write_handler != NULL))
    {
        p_ble_diffusers->main_button_write_handler(p_ble_diffusers, p_evt_write->data[0]);
    }

    if ((p_evt_write->handle == p_ble_diffusers->fan_char_handles.value_handle) &&
            (p_evt_write->len == 1) &&
            (p_ble_diffusers->fan_write_handler != NULL))
    {
        p_ble_diffusers->fan_write_handler(p_ble_diffusers, p_evt_write->data[0]);
    }
}
void ble_diffuser_on_ble_evt(ble_diffuser_t * p_ble_diffusers, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_ble_diffusers, p_ble_evt);
        break;

    case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_ble_diffusers, p_ble_evt);
        break;

    case BLE_GATTS_EVT_WRITE:
        on_write(p_ble_diffusers, p_ble_evt);
        break;

    default:
        // No implementation needed.
        break;
    }
}

uint32_t ble_diffuser_main_button_status_update(ble_diffuser_t * p_diffuser)
{
    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));
    main_button_value = !main_button_value;

    
    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &main_button_value;

    
    // Update database.
    err_code = sd_ble_gatts_value_set(p_diffuser->conn_handle,
                                      p_diffuser->main_button_char_handles.value_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS) {
        return err_code;
    }

    // Send value if connected and notifying.
    if ((p_diffuser->conn_handle != BLE_CONN_HANDLE_INVALID)) {
        ble_gatts_hvx_params_t hvx_params;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_diffuser->main_button_char_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = gatts_value.offset;
        hvx_params.p_len  = &gatts_value.len;
        hvx_params.p_data = gatts_value.p_value;

        err_code = sd_ble_gatts_hvx(p_diffuser->conn_handle, &hvx_params);
    } else {
        err_code = NRF_ERROR_INVALID_STATE;
    }
    return err_code;
}



