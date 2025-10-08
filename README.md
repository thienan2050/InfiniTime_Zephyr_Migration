# [InfiniTime] migration to Zephyr platform.


The purpose of this project is to port and migrate the [InfiniTime] firmware, originally developed using the [NRF52 SDK 15.3.0] and [FreeRTOS], to the [Zephyr platform].

# Milestone
- Release [v1.0] - Hello world application

# Build and flash the source code
PineTime smartwatch board is located at: 
```sh
/InfiniTime_Zephyr_Migration/zephyr-workspace/app/boards/pine64
```
#### Init the zephyr workspace
```sh
git clone https://github.com/thienan2050/InfiniTime_Zephyr_Migration.git
cd InfiniTime_Zephyr_Migration
west init zephyr-workspace --mr v4.2-branch
cd zephyr-workspace
west update
```
#### Build the application:
```sh
cd app
west build -b PineTime_SmartWatch -- -DBOARD_ROOT=../InfiniTime_Zephyr_Migration/zephyr-workspace/app
```
#### Flash the application
```sh
nrfjprog --eraseall -f NRF52 && nrfjprog --program build/zephyr/zephyr.hex --verify --reset && clear&&echo "r\ng\nexit" | JLinkExe -device NRF52 -if SWD -speed 4000 -autoconnect 1
```
# Authors and acknowledgment
[Thien An Bui]

[InfiniTime]: <https://github.com/InfiniTimeOrg/InfiniTime?tab=readme-ov-file>
[NRF52 SDK 15.3.0]:    <https://nsscprodmedia.blob.core.windows.net/prod/software-and-other-downloads/sdks/nrf5/binaries/nrf5sdk153059ac345.zip>
[FreeRTOS]:<https://www.freertos.org>
[Zephyr platform]: <https://www.zephyrproject.org>
[v1.0]: <www.google.com>
[Thien An Bui]: <https://www.facebook.com/ThienAn.SEng>