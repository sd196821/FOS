`define OP_LOAD					7'b0000011
`define OP_LOAD_TYPE					`I_TYPE
`define OP_STORE					7'b0100011
`define OP_STORE_TYPE				`S_TYPE
`define OP_MADD					7'b1000011
`define OP_MADD_TYPE					R4_TYPE
`define OP_BRANCH					7'b1100011
`define OP_BRANCH_TYPE				`SB_TYPE
`define OP_LOAD_FP				7'b0000111
`define OP_LOAD_FP_TYPE				I_TYPE
`define OP_STORE_FP				7'b0100111
`define OP_STORE_FP_TYPE			S_TYPE
`define OP_MSUB					7'b1000111

`define OP_JALR					7'b1100111
`define OP_JALR						`I_TYPE
`define OP_CUSTOM0				7'b0001011

`define OP_CUSTOM1				7'b0101011

`define OP_NMSUB					7'b1001011

`define OP_RESERVED0				7'b1101011

`define OP_MISC_MEM				7'b0001111

`define OP_AMO						7'b0101111
`define OP_AMO_TYPE					`A_TYPE
`define OP_NMADD					7'b1001111

`define OP_JAL						7'b1101111
`define OP_JAL_TYPE					`UJ_TYPE
`define OP_OP_IMM					7'b0010011
`define OP_OP_IMM_TYPE				`I_TYPE
`define OP_OP						7'b0110011
`define OP_OP_TYPE					`R_TYPE
`define OP_OP_FP					7'b1010011
`define OP_OP_FP_TYPE				`R_TYPE
`define OP_SYSTEM					7'b1110011
`define OP_SYSTEM_TYPE				`I_TYPE
`define OP_AUIPC					7'b0010111
`define OP_AUIPC_TYPE				`U_TYPE
`define OP_LUI						7'b0110111
`define OP_LUI_TYPE					`U_TYPE
`define OP_RESERVED1				7'b1010111

`define OP_RESERVED2				7'b1110111

`define OP_OP_IMM_32				7'b0011011
`define OP_OP_IMM_32_TYPE			`I_TYPE
`define OP_OP_32OP_OP_32					7'b0111011
`define OP_OP_32_TYPE				`R_TYPE
`define OP_OP_64_IMM				7'b1011011
`define OP_OP_64					7'b1111011
`define OP_48B						7'b0011111
`define OP_64B						7'b0111111
`define OP_48B						7'b1011111
`define OP_ABOVE80B				7'b1111111