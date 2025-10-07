/*
 * Copyright (c) 2023 Benjamin Cabé <benjamin@zephyrproject.org>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/sensor.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <math.h>
#include <zephyr/logging/log.h>

/* From FreeRTOS InfiniTime */
#include "components/fs/FS.h"
#include "components/settings/Settings.h"
#include "drivers/Spi.h"
#include "drivers/SpiMaster.h"
#include "drivers/SpiNorFlash.h"
#include "drivers/St7789.h"
#include "drivers/TwiMaster.h"
#include "drivers/PinMap.h"
#include "components/datetime/DateTimeController.h"
#include "systemtask/SystemTask.h"


#include "systemtask/Messages.h"

static constexpr uint8_t touchPanelTwiAddress = 0x15;

LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

Pinetime::Drivers::SpiMaster spi {Pinetime::Drivers::SpiMaster::SpiModule::SPI0,
                                  {Pinetime::Drivers::SpiMaster::BitOrder::Msb_Lsb,
                                   Pinetime::Drivers::SpiMaster::Modes::Mode3,
                                   Pinetime::Drivers::SpiMaster::Frequencies::Freq8Mhz,
                                   Pinetime::PinMap::SpiSck,
                                   Pinetime::PinMap::SpiMosi,
                                   Pinetime::PinMap::SpiMiso}};

Pinetime::Drivers::Spi lcdSpi {spi, Pinetime::PinMap::SpiLcdCsn};
Pinetime::Drivers::St7789 lcd {lcdSpi, Pinetime::PinMap::LcdDataCommand, Pinetime::PinMap::LcdReset};

Pinetime::Drivers::Spi flashSpi {spi, Pinetime::PinMap::SpiFlashCsn};
Pinetime::Drivers::SpiNorFlash spiNorFlash {flashSpi};

static constexpr uint32_t MaxTwiFrequencyWithoutHardwareBug {0x06200000};
Pinetime::Drivers::TwiMaster twiMaster {NRF_TWIM1, MaxTwiFrequencyWithoutHardwareBug, Pinetime::PinMap::TwiSda, Pinetime::PinMap::TwiScl};

Pinetime::Controllers::FS fs {spiNorFlash};
Pinetime::Controllers::Settings settingsController {fs};

Pinetime::Controllers::DateTime dateTimeController {settingsController};
Pinetime::Controllers::BrightnessController brightnessController {};


Pinetime::Applications::DisplayApp displayApp(lcd,
                                              //touchPanel,
                                              //batteryController,
                                              //bleController,
                                              dateTimeController,
                                              //watchdog,
                                              //notificationManager,
                                              //heartRateController,
                                              settingsController,
                                              //motorController,
                                              //motionController,
                                              //alarmController,
                                              brightnessController,
                                              //touchHandler,
                                              fs
                                              //spiNorFlash
                                              );


Pinetime::System::SystemTask systemTask(spi,
                                        //spiNorFlash,
                                        twiMaster,
                                        //touchPanel,
                                        //batteryController,
                                        //bleController,
                                        dateTimeController,
                                        //alarmController,
                                        //watchdog,
                                        //notificationManager,
                                        //heartRateSensor,
                                        //motionController,
                                        //motionSensor,
                                        settingsController,
                                        //heartRateController,
                                        displayApp
                                        //heartRateApp,
                                        //fs,
                                        //touchHandler,
                                        //buttonHandler
                                        );


void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void) {
  if (((NRF_SPIM0->INTENSET & (1 << 6)) != 0) && NRF_SPIM0->EVENTS_END == 1) {
    NRF_SPIM0->EVENTS_END = 0;
    //NRF_LOG_INFO("spi.OnEndEvent is triggered!");
    spi.OnEndEvent();
  }

  if (((NRF_SPIM0->INTENSET & (1 << 19)) != 0) && NRF_SPIM0->EVENTS_STARTED == 1) {
    NRF_SPIM0->EVENTS_STARTED = 0;
    //NRF_LOG_INFO("spi.OnStartedEvent is triggered!");
    spi.OnStartedEvent();
  }

  if (((NRF_SPIM0->INTENSET & (1 << 1)) != 0) && NRF_SPIM0->EVENTS_STOPPED == 1) {
    NRF_SPIM0->EVENTS_STOPPED = 0;
  }
}


// static lv_obj_t *chart1;
// static lv_chart_series_t *ser_x;
// static lv_chart_series_t *ser_y;
// static lv_chart_series_t *ser_z;
// static lv_timer_t *sensor_timer;

// const struct device *accel_sensor;

#include <zephyr/drivers/gpio.h>
#define BACKLIGHT_LOW_NODE DT_ALIAS(backlightlow)
#define BACKLIGHT_MID_NODE DT_ALIAS(backlightmid)
#define BACKLIGHT_HIGH_NODE DT_ALIAS(backlighthigh)

const struct gpio_dt_spec bl_low = GPIO_DT_SPEC_GET(BACKLIGHT_LOW_NODE, gpios);
const struct gpio_dt_spec bl_mid = GPIO_DT_SPEC_GET(BACKLIGHT_MID_NODE, gpios);
const struct gpio_dt_spec bl_high = GPIO_DT_SPEC_GET(BACKLIGHT_HIGH_NODE, gpios);
/* Timer handler: fetches sensor data and appends it to the chart */
// static void sensor_timer_cb(lv_timer_t *timer)
// {
// 	struct sensor_value accel[3];
// 	int rc = sensor_sample_fetch(accel_sensor);

// 	if (rc == 0) {
// 		rc = sensor_channel_get(accel_sensor, SENSOR_CHAN_ACCEL_XYZ, accel);
// 	}
// 	if (rc < 0) {
// 		LOG_ERR("ERROR: Update failed: %d\n", rc);
// 		return;
// 	}
// 	lv_chart_set_next_value(chart1, ser_x, sensor_value_to_double(&accel[0]));
// 	lv_chart_set_next_value(chart1, ser_y, sensor_value_to_double(&accel[1]));
// 	lv_chart_set_next_value(chart1, ser_z, sensor_value_to_double(&accel[2]));
// }
// static void sensor_timer_cb(lv_timer_t *timer)
// {
//     static double t = 0;
//     struct sensor_value accel[3];

//     // Dao động chính
//     double base_x = 2.0 * sin(t * 2.0) + 0.5 * cos(t * 5.0);
//     double base_y = 1.5 * sin(t * 1.8 + 1.0) + 0.4 * cos(t * 4.2);
//     double base_z = 1.0 * sin(t * 2.5 + 2.0) + 0.3 * cos(t * 3.5);

//     // Nhiễu ngẫu nhiên ±0.3
//     double noise_x = ((rand() % 100) / 100.0 - 0.5) * 0.6;
//     double noise_y = ((rand() % 100) / 100.0 - 0.5) * 0.6;
//     double noise_z = ((rand() % 100) / 100.0 - 0.5) * 0.6;

//     // Tổng hợp + scale ra m/s² hoặc mg
//     accel[0].val1 = (int)((base_x + noise_x) * 9.81); // m/s²
//     accel[1].val1 = (int)((base_y + noise_y) * 9.81);
//     accel[2].val1 = (int)((base_z + noise_z) * 9.81);

//     accel[0].val2 = 0;
//     accel[1].val2 = 0;
//     accel[2].val2 = 0;

//     t += 0.05; // Tăng thời gian

//     lv_chart_set_next_value(chart1, ser_x, sensor_value_to_double(&accel[0]));
//     lv_chart_set_next_value(chart1, ser_y, sensor_value_to_double(&accel[1]));
//     lv_chart_set_next_value(chart1, ser_z, sensor_value_to_double(&accel[2]));
// }
// static void create_accelerometer_chart(lv_obj_t *parent)
// {
//     chart1 = lv_chart_create(parent);
//     lv_obj_set_size(chart1, LV_HOR_RES, LV_VER_RES);
//     lv_chart_set_type(chart1, LV_CHART_TYPE_LINE);
//     lv_chart_set_div_line_count(chart1, 5, 8);
//     lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, -20, 20); /* roughly -/+ 2G */
//     lv_chart_set_update_mode(chart1, LV_CHART_UPDATE_MODE_SHIFT);

//     ser_x = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_RED),
//                                 LV_CHART_AXIS_PRIMARY_Y);
//     ser_y = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_BLUE),
//                                 LV_CHART_AXIS_PRIMARY_Y);
//     ser_z = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_GREEN),
//                                 LV_CHART_AXIS_PRIMARY_Y);

//     lv_chart_set_point_count(chart1, 50);

//     /* Do not display point markers on the data */
//     lv_obj_set_style_size(chart1, 0, 0, LV_PART_INDICATOR);
// }

int main(void)
{

    const struct device *display_dev;

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev))
    {
        LOG_ERR("Device not ready, aborting test");
        return -ENODEV;
    }
    printk("Hello, world! %d \n", Pinetime::System::Messages::OnNewTime);
    // accel_sensor = DEVICE_DT_GET(DT_ALIAS(accel0));
    // if (!device_is_ready(accel_sensor)) {
    // 	LOG_ERR("Device %s is not ready\n", accel_sensor->name);
    // 	return -ENODEV;
    // }

    gpio_pin_configure_dt(&bl_low, GPIO_OUTPUT_ACTIVE);  // Bật P0.14
    gpio_pin_configure_dt(&bl_mid, GPIO_OUTPUT_ACTIVE);  // Tắt P0.22
    gpio_pin_configure_dt(&bl_high, GPIO_OUTPUT_ACTIVE); // Tắt P0.23
    gpio_pin_set_dt(&bl_low, 1);
    gpio_pin_set_dt(&bl_mid, 1);
    gpio_pin_set_dt(&bl_high, 1);
    // create_accelerometer_chart(lv_screen_active());
    // sensor_timer = lv_timer_create(sensor_timer_cb,
    //                                1000 / 50,
    //                                NULL);
    lv_timer_handler();
    display_blanking_off(display_dev);


    systemTask.Start();

    while (1)
    {
        uint32_t sleep_ms = lv_timer_handler();

        k_msleep(MIN(sleep_ms, INT32_MAX));
        // while(1);
    }

    return 0;
}
