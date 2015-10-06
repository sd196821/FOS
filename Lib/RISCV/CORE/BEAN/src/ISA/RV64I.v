`define RV32I
`include "RV32I.v"
`ifdef RV64I
`define OP_OP_IMM_32_ADDIW			3'b000
`define OP_OP_IMM_32_SLLIW			3'b001
`define OP_OP_IMM_32_SRLIW			3'b101
`define OP_OP_IMM_32_SRAIW			3'b101
`endif
