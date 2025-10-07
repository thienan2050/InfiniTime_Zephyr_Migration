#pragma once
#include <cstddef>
#include <cstdint>

namespace Pinetime {
  namespace Applications {
    enum class Apps : uint8_t {
      None,
      Launcher,
      // Clock,
      // SysInfo,
      // FirmwareUpdate,
      // FirmwareValidation,
      // NotificationsPreview,
      // Notifications,
      // Timer,
      // Alarm,
      // FlashLight,
      // BatteryInfo,
      // Music,
      // Paint,
      // Paddle,
      // Twos,
      // HeartRate,
      // Navigation,
      // StopWatch,
      // Metronome,
      // Motion,
      // Calculator,
      // Steps,
      // Dice,
      // Weather,
      // PassKey,
      // QuickSettings,
      Settings,
      // SettingWatchFace,
      // SettingTimeFormat,
      // SettingWeatherFormat,
      // SettingDisplay,
      // SettingWakeUp,
      // SettingSteps,
      // SettingSetDateTime,
      // SettingChimes,
      // SettingShakeThreshold,
      // SettingBluetooth,
      // MyApp,
      Error
    };

    enum class WatchFace : uint8_t {
      // Digital,
      Analog,
      // PineTimeStyle,
      // Terminal,
      // Infineat,
      // CasioStyleG7710,
      // PrideFlag,
    };

    template <Apps>
    struct AppTraits {};

    template <WatchFace>
    struct WatchFaceTraits {};

    template <Apps... As>
    struct TypeList {
      static constexpr size_t Count = sizeof...(As);
    };

    //using UserAppTypes = TypeList<Apps::MyApp, Apps::StopWatch, Apps::Alarm, Apps::Timer, Apps::Steps, Apps::HeartRate, Apps::Music, Apps::Paint, Apps::Paddle, Apps::Twos, Apps::Dice, Apps::Metronome, Apps::Navigation, Apps::Calculator, Apps::Weather>;
    using UserAppTypes = TypeList<>;
    template <WatchFace... Ws>
    struct WatchFaceTypeList {
      static constexpr size_t Count = sizeof...(Ws);
    };

    //using UserWatchFaceTypes = WatchFaceTypeList<WatchFace::Digital, WatchFace::Analog, WatchFace::PineTimeStyle, WatchFace::Terminal, WatchFace::Infineat, WatchFace::CasioStyleG7710, WatchFace::PrideFlag>;
    using UserWatchFaceTypes = WatchFaceTypeList<WatchFace::Analog>;
    static_assert(UserWatchFaceTypes::Count >= 1);
  }
}
