#pragma once
#include <cstdint>
// #include <lvgl/src/lv_core/lv_obj.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class BatteryIcon {
      public:
        explicit BatteryIcon(bool colorOnLowBattery);
         //Replace by Zephyr OS: void Create(lv_obj_t* parent);

         //Replace by Zephyr OS: void SetColor(lv_color_t);
        void SetBatteryPercentage(uint8_t percentage);
         //Replace by Zephyr OS: lv_obj_t* GetObject();

        static const char* GetUnknownIcon();
        static const char* GetPlugIcon(bool isCharging);

      private:
         //Replace by Zephyr OS: lv_obj_t* batteryImg;
         //Replace by Zephyr OS: lv_obj_t* batteryJuice;
        bool colorOnLowBattery = false;
      };
    }
  }
}
