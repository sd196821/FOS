`define RV32F
`include "RV32F.v"
`ifdef RV64F 
`define OP_OP_FP_FCVTLS				10'b1100000111
`define OP_OP_FP_FCVTLUS			10'b1100000111
`define OP_OP_FP_FCVTSL				10'b1101000111
`define OP_OP_FP_FCVTSLU			10'b1101000111
`endif
