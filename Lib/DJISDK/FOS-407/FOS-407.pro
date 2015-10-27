TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    App/main.cpp \
    HardDrivers/key.c \
    HardDrivers/led.c \
    HardDrivers/rtc.c \
    StartUp/system_stm32f4xx.c \
    STM32F40X_Lib/src/misc.c \
    STM32F40X_Lib/src/stm32f4xx_adc.c \
    STM32F40X_Lib/src/stm32f4xx_can.c \
    STM32F40X_Lib/src/stm32f4xx_crc.c \
    STM32F40X_Lib/src/stm32f4xx_cryp.c \
    STM32F40X_Lib/src/stm32f4xx_cryp_aes.c \
    STM32F40X_Lib/src/stm32f4xx_cryp_des.c \
    STM32F40X_Lib/src/stm32f4xx_cryp_tdes.c \
    STM32F40X_Lib/src/stm32f4xx_dac.c \
    STM32F40X_Lib/src/stm32f4xx_dbgmcu.c \
    STM32F40X_Lib/src/stm32f4xx_dcmi.c \
    STM32F40X_Lib/src/stm32f4xx_dma.c \
    STM32F40X_Lib/src/stm32f4xx_dma2d.c \
    STM32F40X_Lib/src/stm32f4xx_exti.c \
    STM32F40X_Lib/src/stm32f4xx_flash.c \
    STM32F40X_Lib/src/stm32f4xx_fsmc.c \
    STM32F40X_Lib/src/stm32f4xx_gpio.c \
    STM32F40X_Lib/src/stm32f4xx_hash.c \
    STM32F40X_Lib/src/stm32f4xx_hash_md5.c \
    STM32F40X_Lib/src/stm32f4xx_hash_sha1.c \
    STM32F40X_Lib/src/stm32f4xx_i2c.c \
    STM32F40X_Lib/src/stm32f4xx_iwdg.c \
    STM32F40X_Lib/src/stm32f4xx_ltdc.c \
    STM32F40X_Lib/src/stm32f4xx_pwr.c \
    STM32F40X_Lib/src/stm32f4xx_rcc.c \
    STM32F40X_Lib/src/stm32f4xx_rng.c \
    STM32F40X_Lib/src/stm32f4xx_rtc.c \
    STM32F40X_Lib/src/stm32f4xx_sai.c \
    STM32F40X_Lib/src/stm32f4xx_sdio.c \
    STM32F40X_Lib/src/stm32f4xx_spi.c \
    STM32F40X_Lib/src/stm32f4xx_syscfg.c \
    STM32F40X_Lib/src/stm32f4xx_tim.c \
    STM32F40X_Lib/src/stm32f4xx_usart.c \
    STM32F40X_Lib/src/stm32f4xx_wwdg.c \
    FOSLib/usart.cpp \
    FOSLib/n1sdk.cpp \
    DJISDK/DJI_Pro_App.cpp \
    DJISDK/DJI_Pro_Codec.cpp \
    DJISDK/DJI_Pro_Hw.cpp \
    DJISDK/DJI_Pro_Link.cpp \
    DJISDK/DJI_Pro_Test.cpp \
    FOSLib/littletask.cpp \
    FOSLib/gpio.cpp \
    FOSLib/rplidar.cpp \
    FOSLib/wall.cpp \
    FOSLib/servo.cpp \
    HardDrivers/spi_flash.cpp \
    FOSLib/cppforstm32.cpp \
    FOSLib/flightcontrol.cpp \
    FlightControl/cv.cpp \
    FlightControl/upperdecode.cpp \
    FlightControl/logic.cpp \
    App/mechanical.cpp \
    FOSLib/V1.0/fos.cpp

HEADERS += \
    HardDrivers/key.h \
    HardDrivers/led.h \
    HardDrivers/rtc.h \
    HardDrivers/spi_flash.h \
    StartUp/stm32f4xx.h \
    StartUp/stm32f4xx_conf.h \
    StartUp/system_stm32f4xx.h \
    STM32F40X_Lib/inc/misc.h \
    STM32F40X_Lib/inc/stm32f4xx_adc.h \
    STM32F40X_Lib/inc/stm32f4xx_can.h \
    STM32F40X_Lib/inc/stm32f4xx_crc.h \
    STM32F40X_Lib/inc/stm32f4xx_cryp.h \
    STM32F40X_Lib/inc/stm32f4xx_dac.h \
    STM32F40X_Lib/inc/stm32f4xx_dbgmcu.h \
    STM32F40X_Lib/inc/stm32f4xx_dcmi.h \
    STM32F40X_Lib/inc/stm32f4xx_dma.h \
    STM32F40X_Lib/inc/stm32f4xx_dma2d.h \
    STM32F40X_Lib/inc/stm32f4xx_exti.h \
    STM32F40X_Lib/inc/stm32f4xx_flash.h \
    STM32F40X_Lib/inc/stm32f4xx_fsmc.h \
    STM32F40X_Lib/inc/stm32f4xx_gpio.h \
    STM32F40X_Lib/inc/stm32f4xx_hash.h \
    STM32F40X_Lib/inc/stm32f4xx_i2c.h \
    STM32F40X_Lib/inc/stm32f4xx_iwdg.h \
    STM32F40X_Lib/inc/stm32f4xx_ltdc.h \
    STM32F40X_Lib/inc/stm32f4xx_pwr.h \
    STM32F40X_Lib/inc/stm32f4xx_rcc.h \
    STM32F40X_Lib/inc/stm32f4xx_rng.h \
    STM32F40X_Lib/inc/stm32f4xx_rtc.h \
    STM32F40X_Lib/inc/stm32f4xx_sai.h \
    STM32F40X_Lib/inc/stm32f4xx_sdio.h \
    STM32F40X_Lib/inc/stm32f4xx_spi.h \
    STM32F40X_Lib/inc/stm32f4xx_syscfg.h \
    STM32F40X_Lib/inc/stm32f4xx_tim.h \
    STM32F40X_Lib/inc/stm32f4xx_usart.h \
    STM32F40X_Lib/inc/stm32f4xx_wwdg.h \
    FOSLib/usart.h \
    FOSLib/n1sdk.h \
    DJISDK/DJI_Pro_App.h \
    DJISDK/DJI_Pro_Codec.h \
    DJISDK/DJI_Pro_Hw.h \
    DJISDK/DJI_Pro_Link.h \
    DJISDK/DJI_Pro_Test.h \
    FOSLib/littletask.h \
    FOSLib/DJI_Pro_Type.h \
    FOSLib/encodeType.h \
    FOSLib/gpio.h \
    FOSLib/rplidar.h \
    FOSLib/wall.h \
    FOSLib/servo.h \
    FOSLib/cppforstm32.h \
    FOSLib/flightcontrol.h \
    FlightControl/StateMachine.h \
    FlightControl/cv.h \
    FlightControl/upperdecode.h \
    FlightControl/logic.h \
    App/mechanical.h \
    FOSLib/V1.0/fos.h

OTHER_FILES += \
    Project/List/RTC.map \
    Project/List/startup_stm32f2xx.lst \
    Project/List/startup_stm32f10x_hd.lst \
    Project/List/startup_stm32f40_41xxx.lst \
    StartUp/startup_stm32f40_41xxx.s

INCLUDEPATH += \
    App \
    FOSLib \
    HardDrivers \
    StartUp \
    STM32F40x_Lib/inc \
    STM32F40x_Lib/src \
    DJISDK \
    FlightControl \
    FOSLib/V1.0

DEFINES += \
    STM32 \
    STM32F40x \
    USE_STDPERIPH_DRIVER \
    STM32F40_41xxx \
    USE_STM324xG_EVAL \
    __FPU_USED = 1 \
    DYNAMIC_MEMORY \
    DEBUG \
    USE_QT
