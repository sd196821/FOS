`define RV32A
`include "RV32A.v"
`ifdef  RV64A
`define OP_AMO_LRD					8'b00010011
`define OP_AMO_SCD   	         8'b00011011
`define OP_AMO_AMOSWAPD 	      8'b00001011
`define OP_AMO_AMOADDD     	   8'b00000011
`define OP_AMO_AMOXORD        	8'b00100011
`define OP_AMO_AMOANDD     	   8'b01100011
`define OP_AMO_AMOORD         	8'b01000011
`define OP_AMO_AMOMIND	  	      8'b10000011
`define OP_AMO_AMOMAXD     	   8'b10100011
`define OP_AMO_AMOMINUD       	8'b11000011
`define OP_AMO_AMOMAXUD 	      8'b11100011
`endif
