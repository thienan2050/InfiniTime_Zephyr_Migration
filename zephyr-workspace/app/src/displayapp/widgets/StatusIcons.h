#pragma once

// #include <lvgl/lvgl.h>

#include "displayapp/screens/Screen.h"
#include "components/battery/BatteryController.h"
// #include "components/ble/BleController.h"
#include "components/alarm/AlarmController.h"
#include "displayapp/screens/BatteryIcon.h"
#include "utility/DirtyValue.h"

namespace Pinetime {
  namespace Applications {
    namespace Widgets {
      class StatusIcons {
      public:
        StatusIcons(const Controllers::Battery& batteryController,
                    const Controllers::Ble& bleController,
                    const Controllers::AlarmController& alarmController);
        void Align();
        void Create();

        //Replace by Zephyr OS: lv_obj_t* GetObject() {
          //Replace by Zephyr OS:return container;
        //Replace by Zephyr OS:}

        void Update();

      private:
        Screens::BatteryIcon batteryIcon;
        const Pinetime::Controllers::Battery& batteryController;
        const Controllers::Ble& bleController;
        const Controllers::AlarmController& alarmController;

        Utility::DirtyValue<uint8_t> batteryPercentRemaining {};
        Utility::DirtyValue<bool> powerPresent {};
        Utility::DirtyValue<bool> bleState {};
        Utility::DirtyValue<bool> bleRadioEnabled {};
        Utility::DirtyValue<bool> alarmEnabled {};

         //Replace by Zephyr OS: lv_obj_t* bleIcon;
         //Replace by Zephyr OS: lv_obj_t* alarmIcon;
         //Replace by Zephyr OS: lv_obj_t* batteryPlug;
         //Replace by Zephyr OS: lv_obj_t* container;
      };
    }
  }
}
