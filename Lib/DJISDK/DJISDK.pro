TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += \
    DJI_LIB \
    RTE \
    RTE/Device/STM32F407ZGTx \
    RTE/Device/STM32F407ZGTx/STCubeGenerated \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMISIS/Include \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Inc \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc

HEADERS += \
    RTE/RTE_Components.h \
    RTE/Device/STM32F407ZGTx/MX_Device.h \
    DJI_LIB/DJI_Pro_App.h \
    DJI_LIB/DJI_Pro_Codec.h \
    DJI_LIB/DJI_Pro_Config.h \
    DJI_LIB/DJI_Pro_Hw.h \
    DJI_LIB/DJI_Pro_Link.h \
    DJI_LIB/DJI_Pro_Rmu.h \
    DJI_Pro_Sample.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f407xx.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/croutine.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/deprecated_definitions.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/event_groups.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/FreeRTOS.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/FreeRTOSConfig_template.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/list.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/mpu_wrappers.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/portable.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/projdefs.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/queue.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/semphr.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/StackMacros.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/task.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/inc/timers.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/portmacro.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Inc/FreeRTOSConfig.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Inc/mxconstants.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Inc/stm32f4xx_hal_conf.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Inc/stm32f4xx_it.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_can.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cec.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_conf_template.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_crc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cryp.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cryp_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dcmi.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dcmi_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma2d.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dsi.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_eth.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_fmpi2c.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_fmpi2c_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hash.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hash_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2s.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2s_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_irda.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_iwdg.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_lptim.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_ltdc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_ltdc_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_nand.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_nor.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pccard.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pcd.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pcd_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_qspi.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rtc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rtc_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_sai.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_sai_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_sd.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_sdram.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_smartcard.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_spdifrx.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_spi.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_sram.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_usart.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_wwdg.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fsmc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_sdmmc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/arm_common_tables.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/arm_const_structs.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/arm_math.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cm0.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cm0plus.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cm3.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cm4.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cm7.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cmFunc.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cmInstr.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_cmSimd.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_sc000.h \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/CMSIS/Include/core_sc300.h

DISTFILES += \
    RTE/Device/STM32F407ZGTx/startup_stm32f407xx.s

SOURCES += \
    RTE/Device/STM32F407ZGTx/system_stm32f4xx.c \
    DJI_LIB/DJI_Pro_App.cpp \
    DJI_LIB/DJI_Pro_Codec.cpp \
    DJI_LIB/DJI_Pro_Hw.cpp \
    DJI_LIB/DJI_Pro_Link.cpp \
    DJI_LIB/DJI_Pro_Rmu.cpp \
    DJI_Pro_Sample.cpp \
    RTE/CMSIS/RTX_Conf_CM.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Src/freertos.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Src/main.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Src/stm32f4xx_hal_msp.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Src/stm32f4xx_it.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/list.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/timers.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_2.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/port.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_msp_template.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
    RTE/Device/STM32F407ZGTx/STCubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c

DEFINES += \
    STM32F407xx
