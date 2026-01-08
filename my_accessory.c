#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
    printf("accessory identify\n");
}

// Desk and ceiling perlin switches
homekit_characteristic_t switch_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t switch_name = HOMEKIT_CHARACTERISTIC_(NAME, "Switch 1");

// Desk LED characteristics
homekit_characteristic_t on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t name = HOMEKIT_CHARACTERISTIC_(NAME, "Wardrobe Lights");
homekit_characteristic_t bright = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 100);
homekit_characteristic_t sat = HOMEKIT_CHARACTERISTIC_(SATURATION, (float) 0);
homekit_characteristic_t hue = HOMEKIT_CHARACTERISTIC_(HUE, (float) 180);

// Accessories array
homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_bridge, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "XeWe Lights Wardrobe"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "XeWe Industries"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "17-19-67-69"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "3.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=2, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) { 
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Wardrobe Lights"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &on,
            &name,
            &bright,
            &sat,
            &hue,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=3, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) { 
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Wardrobe Lights Fade"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            &switch_on,
            &switch_name,
            NULL
        }),
        NULL
    }),
    NULL
};

// Server configuration
homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"
};
