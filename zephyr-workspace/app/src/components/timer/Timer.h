#pragma once

// #include <FreeRTOS.h>
// #include <timers.h>

#include <chrono>

namespace Pinetime {
  namespace Controllers {
    class Timer {
    public:
      //Replace by Zephyr OS: Timer(void* timerData, TimerCallbackFunction_t timerCallbackFunction);

      void StartTimer(std::chrono::milliseconds duration);

      void StopTimer();

      std::chrono::milliseconds GetTimeRemaining();

      bool IsRunning();

    private:
      //Replace by Zephyr OS: TimerHandle_t timer;
    };
  }
}
