#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

homekit_characteristic_t cha_switch_on1 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on2 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on3 = HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_switch_on4 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on5 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on6 = HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_switch_on7 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on8 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on9 = HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_switch_on10 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on11 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on12 = HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_switch_on13 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on14 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on15 = HOMEKIT_CHARACTERISTIC_(ON, false);

homekit_characteristic_t cha_switch_on16 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on17 = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_switch_on18 = HOMEKIT_CHARACTERISTIC_(ON, false);




homekit_characteristic_t cha_name1 = HOMEKIT_CHARACTERISTIC_(NAME, "第1键单击");
homekit_characteristic_t cha_name2 = HOMEKIT_CHARACTERISTIC_(NAME, "第1键双击");
homekit_characteristic_t cha_name3 = HOMEKIT_CHARACTERISTIC_(NAME, "第1键长按");

homekit_characteristic_t cha_name4 = HOMEKIT_CHARACTERISTIC_(NAME, "第2键单击");
homekit_characteristic_t cha_name5 = HOMEKIT_CHARACTERISTIC_(NAME, "第2键双击");
homekit_characteristic_t cha_name6 = HOMEKIT_CHARACTERISTIC_(NAME, "第2键长按");

homekit_characteristic_t cha_name7 = HOMEKIT_CHARACTERISTIC_(NAME, "第3键单击");
homekit_characteristic_t cha_name8 = HOMEKIT_CHARACTERISTIC_(NAME, "第3键双击");
homekit_characteristic_t cha_name9 = HOMEKIT_CHARACTERISTIC_(NAME, "第3键长按");

homekit_characteristic_t cha_name10 = HOMEKIT_CHARACTERISTIC_(NAME, "第4键单击");
homekit_characteristic_t cha_name11 = HOMEKIT_CHARACTERISTIC_(NAME, "第4键双击");
homekit_characteristic_t cha_name12 = HOMEKIT_CHARACTERISTIC_(NAME, "第4键长按");

homekit_characteristic_t cha_name13 = HOMEKIT_CHARACTERISTIC_(NAME, "第5键单击");
homekit_characteristic_t cha_name14 = HOMEKIT_CHARACTERISTIC_(NAME, "第5键双击");
homekit_characteristic_t cha_name15 = HOMEKIT_CHARACTERISTIC_(NAME, "第5键长按");

homekit_characteristic_t cha_name16 = HOMEKIT_CHARACTERISTIC_(NAME, "第6键单击");
homekit_characteristic_t cha_name17 = HOMEKIT_CHARACTERISTIC_(NAME, "第6键双击");
homekit_characteristic_t cha_name18 = HOMEKIT_CHARACTERISTIC_(NAME, "第6键长按");


homekit_accessory_t *accessories[] = {
 HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_outlet, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "HM通讯模块"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "HM通讯模块"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "m805500091"),
            HOMEKIT_CHARACTERISTIC(MODEL, "H-M"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
      HOMEKIT_SERVICE(OUTLET,.primary=true, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on1,
      &cha_name1,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on2,
      &cha_name2,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on3,
      &cha_name3,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on4,
      &cha_name4,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on5,
      &cha_name5,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on6,
      &cha_name6,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on7,
      &cha_name7,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on8,
      &cha_name8,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on9,
      &cha_name9,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on10,
      &cha_name10,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on11,
      &cha_name11,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on12,
      &cha_name12,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on13,
      &cha_name13,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on14,
      &cha_name14,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on15,
      &cha_name15,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on16,
      &cha_name16,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on17,
      &cha_name17,
      NULL
    }),
      HOMEKIT_SERVICE(OUTLET, .characteristics=(homekit_characteristic_t*[]){
      &cha_switch_on18,
      &cha_name18,
      NULL
    }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "123-11-111"
};
