`ifdef  RV32I
`define OP_LOAD_LB					3'b000
`define OP_LOAD_LH					3'b001
`define OP_LOAD_LW					3'b010
`define OP_LOAD_LBU					3'b100
`define OP_LOAD_LHU					3'b101

`define OP_BRANCH_BEQ				3'b000
`define OP_BRANCH_BNE				3'b001
`define OP_BRANCH_BLT				3'b100
`define OP_BRANCH_BGE				3'b101
`define OP_BRANCH_BLTU				3'b110
`define OP_BRANCH_BGEU				3'b111

`define OP_JALR_JALR					3'b000

`define OP_STORE_SB					3'b000
`define OP_STORE_SH					3'b001
`define OP_STORE_SW					3'b010

`define OP_MISC_MEM_FENCE			3'b000
`define OP_MISC_MEM_FENCEI 		3'b001

`define OP_OP_IMM_ADDI				3'b000
`define OP_OP_IMM_SLTI				3'b010
`define OP_OP_IMM_SLTIU				3'b011
`define OP_OP_IMM_XORI				3'b100
`define OP_OP_IMM_ORI				3'b110
`define OP_OP_IMM_ANDI				3'b111
`define OP_OP_IMM_SLLI				3'b001
`define OP_OP_IMM_SRLI				3'b101
`define OP_OP_IMM_SRLI_DATA		2'b00
`define OP_OP_IMM_SRAI				3'b101
`define OP_OP_IMM_SRAI_DATA		2'b01

`define OP_OP_ADD						10'b0000000000
`define OP_OP_SUB						10'b0100000000
`define OP_OP_SLL						10'b0000000001
`define OP_OP_SLT						10'b0000000010
`define OP_OP_SLTU					10'b0000000011
`define OP_OP_XOR						10'b0000000100
`define OP_OP_SRL						10'b0000000101
`define OP_OP_SRA						10'b0100000101
`define OP_OP_OR						10'b0000000110
`define OP_OP_AND						10'b0000000111

`define OP_SYSTEM_SCALL				3'b000
`define OP_SYSTEM_SCALL_DATA		12'b000000000000
`define OP_SYSTEM_SBREAK			3'b000
`define OP_SYSTEM_SBREAK_DATA		12'b000000000001
`define OP_SYSTEM_RDCYCLE			3'b010
`define OP_SYSTEM_RDCYCLE_DATA	12'b110000000000
`define OP_SYSTEM_RDCYCLEH			3'b010
`define OP_SYSTEM_RDCYCLEH_DATA	12'b110010000000
`define OP_SYSTEM_RDTIME			3'b010
`define OP_SYSTEM_RDTIME_DATA		12'b110010000001
`define OP_SYSTEM_RDTIMEH			3'b010
`define OP_SYSTEM_RDTIMEH_DATA	12'b110010000001
`define OP_SYSTEM_RDSTRET			3'b010
`define OP_SYSTEM_RDSTRET_DATA	12'b110010000010
`define OP_SYSTEM_RDSTRETH			3'b010
`define OP_SYSTEM_RDSTRETH_DATA	12'b110010000010
`endif
