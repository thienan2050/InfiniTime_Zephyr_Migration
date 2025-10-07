#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

#include <FreeRTOS.h>
#include "portmacro_cmsis.h"

#include "systemtask/SystemTask.h"
#include "systemtask/WakeLock.h"
#include "displayapp/apps/Apps.h"
#include "displayapp/Controllers.h"
#include "Symbols.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class MyApp : public Screen {
      public:
        explicit MyApp(AppControllers& controllers);
        ~MyApp() override;

        void Refresh() override;
        bool OnButtonPushed() override;
      private:
        lv_task_t* taskRefresh;
      };
    }

    // AppTraits specialization
    template <>
    struct AppTraits<Apps::MyApp> {
      static constexpr Apps app = Apps::MyApp;
      static constexpr const char* icon = Screens::Symbols::heartBeat;  

      static Screens::Screen* Create(AppControllers& controllers) {
        return new Screens::MyApp(controllers);
      }

      static bool IsAvailable(Pinetime::Controllers::FS&) {
        return true;
      }
    };
  }
}
