`define RV32I
`include "RV32I.v"
`ifdef RV64I
`define OP_OP_IMM_32_ADDIW			3'b000
`define OP_OP_IMM_32_SLLIW			3'b001
`define OP_OP_IMM_32_SRLIW			3'b101
`define OP_OP_IMM_32_SRAIW			3'b101

`define OP_OP_32_ADDW				10'b0000000000
`define OP_OP_32_SUBW				10'b0000000000
`define OP_OP_32_SLLW				10'b0000000001
`define OP_OP_32_SRLW				10'b0000000101
`define OP_OP_32_SRAW				10'b0000000101

`define OP_LOAD_LWU					3'b110
`define OP_LOAD_LD					3'b011

`define OP_STORE_SD					3'b011
`endif
