cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(InfiniTime_Zephyr C CXX)

set(NORDIC_SDK_PATH /Users/an.bui-thien/Downloads/nRF5_SDK_15.3.0_59ac345)

target_include_directories(app PRIVATE 
    src 
    src/systemtask 
    src/components/datetime 
    src/components/fs 
    src/components/settings
    src/components/datetime
    src/components/firmwarevalidator
    src/systemtask
    src/displayapp 
    src/drivers
    src/littlefs
    ${NORDIC_SDK_PATH}/modules/nrfx/drivers/include
    ${NORDIC_SDK_PATH}/modules/nrfx/hal
    ${NORDIC_SDK_PATH}/components/libraries/util
    ${NORDIC_SDK_PATH}/components
    ${NORDIC_SDK_PATH}/components/softdevice/s112/headers
    ${NORDIC_SDK_PATH}/external/freertos/source/include
    )


target_sources(app PRIVATE
    src/main_testing.cpp
    src/drivers/SpiMaster.cpp
    src/drivers/Spi.cpp
    src/drivers/St7789.cpp
    src/drivers/SpiNorFLash.cpp
    src/drivers/TwiMaster.cpp
    src/components/fs/FS.cpp
    src/littlefs/lfs.c
    src/components/settings/Settings.cpp
    src/components/datetime/DateTimeController.cpp
    src/components/firmwarevalidator/FirmwareValidator.cpp
    src/displayapp/DisplayApp.cpp
    src/displayapp/LittleVgl.cpp
    src/systemtask/SystemTask.cpp
)
