#pragma once
// #include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Widgets {
      class PageIndicator {
      public:
        PageIndicator(uint8_t nCurrentScreen, uint8_t nScreens);
        void Create();

      private:
        uint8_t nCurrentScreen;
        uint8_t nScreens;

         //Replace by Zephyr OS: lv_point_t pageIndicatorBasePoints[2];
         //Replace by Zephyr OS: lv_point_t pageIndicatorPoints[2];
         //Replace by Zephyr OS: lv_obj_t* pageIndicatorBase;
         //Replace by Zephyr OS: lv_obj_t* pageIndicator;
      };
    }
  }
}
