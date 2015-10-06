`define RV32M
`include "RV32M.v"
`ifdef RV64M
`define OP_OP_32_MULW				10'b0000001000	
`define OP_OP_32_DIVW				10'b0000001100
`define OP_OP_32_DIVUW				10'b0000001101
`define OP_OP_32_REMW				10'b0000001110
`define OP_OP_32_REMUW				10'b0000001111
`endif