#BEAN

##Logical Simulation

- FPGA Model：SPARTAN-6
- Device	：DDR3
- I/O		：



##ISA

RV64G

|**inst[4:2]/inst[6:5]**|**000**|**001**	|**010**	|**011**	|**100**|**101**	|**110**	|**111**|
|-----------------------|-------|-----------|-----------|-----------|-------|-----------|-----------|-------|
|00						|LOAD	|LOAD-FP	|custom-0	|MISC-MEM	|OP-IMM	|AUIPC		|OP-IMM-32	|48b	|
|01						|STORE	|STORE-FP	|custom-1	|AMO		|OP		|LUI		|OP-32		|64b	|
|10						|MADD	|MSUB		|NMSUB		|NMADD		|OP-FP	|reserved	|rv128		|48b	|
|11						|BRANCH	|JALR		|reserved	|JAL		|SYSTEM	|reserved	|rv128		|>80b	|

##System structure


![](https://github.com/justwillim/FOS/blob/Development/Lib/RISCV/Document/EN/img/Core.jpg)






