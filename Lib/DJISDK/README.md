[EN](#user-content-E0)|[中文](#user-content-C0)

#MOC-DJISDK

MOC-DJISDK，is a DJI-onboardSDK for ARM 32-bit Cortex-M4（STM32F4）or higher preformance embessed system.

<p  id="E0">

#Contents

- [Quick Start](#user-content-E1)

- [Overview](#user-content-E2) 

- [API](#user-content-E3) 

- [FAQ](#user-content-E4)

- [Do & Don't](#user-content-E5)

#Quick Start

<p  id="E1">

We strongly suggest you to read this part, no matter it is your first time or not.

##Hardware Checklist 

-M100

-STM32F407 Miniun system.

-STLink 1 pics.

-BEC 5V3A or higher.

-CP2102 module 2 pics.

-UART RF module 4 pics.

-Appropriate amount of DoPont wire， 3M foamed double-sided hesive tape.

##Software Enviroment

-MDK5(Keil uVision5)

If your PC is running in a Unix-like system or a Mac OS, you can install MDK5 with wine.

-QT5.5 or height version

##Tools

-Multimeter

-2s test battery for BEC with XT60 (optional)

##Build up steps

###Power Module

-Soldering XT60 （given by M100 fittings） to BEC.

-Connect BEC to M100.

-Start M100, use multieter to test if BEC is working correctly or not.

-(Plan A) Soldering BEC output to STM32 board.

-(Plan B) Soldering BEC output to a JST

-(Plan B step 2) Soldering JST to STM32 board.

###System

-Link BEC and STM32 board (or it is already soldered).

-Link BEC to test battery or M100 and Start it.

-Check if STM32 board is running or not.

-Power off.

-Link STLink to STM32 board

	-at lesat 3 wires
	
	-GND

	-SCK

	-SDO

-Link STLink to PC

-Power on.

###Software Eniroment test

-


#Overview

<p  id="E2">

#API

<p  id="E3">

#FAQ

<p  id="E4">

#Do & Don't

<p  id="E5">



<p  id="C0">


#MOC-DJISDK

魔改版DJISDK，适用于ARM 32-bit Cortex-M4（STM32F4）及其性能以上的嵌入式系统或嵌入式PC。

#目录

- [快速启动](#user-content-C1)

- [概述](#user-content-C2) 

- [API接口说明](#user-content-C3) 

- [常见问题](#user-content-C4)

- [注意事项](#user-content-C5)

#快速启动

<p  id="C1">

我们强烈建议您阅读此章节，无论是否是第一次使用。

##硬件设备清单

-M100飞行器套件；

-STM32F407最小系统；

-STLink；

-BEC稳压单元 5V3A 或更高功率；

-CP2102 USB-TTL 串口模块 2个；

-无线串口模块 4个；

-杜邦线、3M发泡贴纸适量；

##软件环境

-MDK5（Keil uVision5）；

如果您是Unix 或 Mac OS用户 可以使用wine来安装MDK5。

-QT5.5 或更高版本



#概述

<p  id="C2">

#API接口说明

<p  id="C3">

#常见问题

<p  id="C4">


#注意事项

<p  id="C5">

