#Abstract

Forest Operating System (FOS) is a concurrently, distributed, 
cuttable, real-time operating system framework.

It is contructed form hardware level, to application level.

#Contents

- [Over view](#user-cotent-0)

- [Computing Node](#user-content-1)

- [UAV Control Model](#user-content-2) 

- [Group Control Model](#user-content-3) 

- [Radio communication](#user-content-4)

- [Communication Protocol Stack](#user-content-5)

- [topological](#user-content-6)

- [Muliti Group](#user-content-7)

#Over view

<p  id="0">

#Computing Node

<p  id="1">

##Brief
##Model
###Firmware model

![](img/ComputingNode.jpg)

###Data stream model

![](img/ComputingNode2.jpg)

###Network model

![](img/ComputingNode3.jpg)
 

##Memory Management Unit (MMU)

###Brief
In FOS, every computing Node is contructed by a core unit whitch is a MMU.
FOS's MMU can be a soft implementation, 
a hard implementation or a mixed implementation.

In order to actrualize this unit easily, 

MMU's I/O is mulitable,


###Model

###Actrualize

###I/O





##Linker
###Brief
Linker is a specific data stack, which is used to share data between two different computing node.
###Model

##Data stacks
###Brief
###Model


<p  id="2">

#UAV Control Model
###Brief
###Model

![](img/UAVControl1.jpg)

As a black box, this Control model seems like:

![](img/UAVControl2.jpg)

Or in real world it seems like:

![](img/UAVControl3.jpg)

<p  id="3">

#Group Control Model

##Problem Model

![](img/Group1.jpg)

##Basic Model
##Promotion

<p  id="4">

#Radio communication

![](img/Group2.jpg)

As a radio data transport device, there're 4 things needs to consider:
frequency, channel, power and stack.

In this case, we provide a full functional stack, including features below:

- Secret communication
- Automatic frequency hopping
- Global broadcast
- Auto topology construction
- Signal intensity detection
- Flexible baud rate

State machine

![](img/Radio1.jpg)

<p  id="5">

#Communication Protocol Stack

<p  id="6">

#Topological

<p  id="7">

#Muliti Group

##Problem Model
![](img/Group3.jpg)