#include <zephyr/kernel.h>
#include <lvgl.h>
#include "lv_demo_benchmark.h"
#include <zephyr/drivers/gpio.h>

#define BACKLIGHT_LOW_NODE DT_ALIAS(backlightlow)
#define BACKLIGHT_MID_NODE DT_ALIAS(backlightmid)
#define BACKLIGHT_HIGH_NODE DT_ALIAS(backlighthigh)

const struct gpio_dt_spec bl_low = GPIO_DT_SPEC_GET(BACKLIGHT_LOW_NODE, gpios);
const struct gpio_dt_spec bl_mid = GPIO_DT_SPEC_GET(BACKLIGHT_MID_NODE, gpios);
const struct gpio_dt_spec bl_high = GPIO_DT_SPEC_GET(BACKLIGHT_HIGH_NODE, gpios);
const struct device *display_dev;

static int set_backlight_on(void)
{
#if defined(CONFIG_BACKLIGHT_FIRMWARE)

    #define BACKLIGHT_GPIO_DEV  DT_PHANDLE_BY_IDX(DT_ALIAS(backlight), gpios, 0)
    #define BACKLIGHT_PIN       DT_GPIO_PIN(DT_ALIAS(backlight), gpios)
    #define BACKLIGHT_FLAGS     DT_GPIO_FLAGS(DT_ALIAS(backlight), gpios)

    static const struct device * gpio;

    LOG_INF("Backlight firmware configured");

    gpio = DEVICE_DT_GET(BACKLIGHT_GPIO_DEV);
    if (!gpio) {
        return -1;
    }

    gpio_pin_configure(gpio, BACKLIGHT_PIN, GPIO_OUTPUT);
    gpio_pin_set(gpio, BACKLIGHT_PIN, 1);

    return 0;

#elif defined(CONFIG_BACKLIGHT_MANUAL)

    LOG_INF("Backlight manually configured");
    return 0;

#else

    LOG_ERR("Set Backlight configuration method");
    return 0   ;

#endif
}



int main(void) {

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        LOG_ERR("Device not ready, aborting");
        return 0;
    }

    if (set_backlight_on() < 0) {
        LOG_ERR("Backlight failure: aborting");
        return 0;
    }


    lv_demo_benchmark();
        display_blanking_off(display_dev);
    gpio_pin_configure_dt(&bl_low, GPIO_OUTPUT_ACTIVE);  // Bật P0.14
    gpio_pin_configure_dt(&bl_mid, GPIO_OUTPUT_ACTIVE);  // Tắt P0.22
    gpio_pin_configure_dt(&bl_high, GPIO_OUTPUT_ACTIVE); // Tắt P0.23
    gpio_pin_set_dt(&bl_low, 1);
    gpio_pin_set_dt(&bl_mid, 1);
    gpio_pin_set_dt(&bl_high, 1);
    while (1) {
        k_sleep(K_MSEC(100));
        lv_task_handler();
    }
    return 1;
}
