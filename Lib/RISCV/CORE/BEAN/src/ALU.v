`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:07:48 10/01/2015 
// Design Name: 
// Module Name:    ALU 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

`include "BEAN.cfg"
`include "ALU.cfg"
module ALU(
				input [`ALU_OP_WIDTH-1:0] op,
				input [`XPR_LEN-1:0] rs1,
				input [`XPR_LEN-1:0] rs2,
				output reg [`XPR_LEN-1:0] rd,
				input clk,
				input enable
				);

wire[`SHAMT_WIDTH-1:0] shamt;
wire[`W_LEN-1:0] rs1W;
assign shamt = rs2[`SHAMT_WIDTH-1:0];
assign rs1W  = rs1[`W_LEN-1:0];
always @(posedge clk)
begin
	if(enable)
		case(op)
			`ALU_OP_ADD : rd <= rs1 + rs2;
			`ALU_OP_SLL : rd <= rs1 << shamt;
			`ALU_OP_SLT : rd <= {`XPR_LEN-1'b0,$signed(rs1) <  $signed(rs2)};
			`ALU_OP_SLTU: rd <= {`XPR_LEN-1'b0,rs1<rs2};
			`ALU_OP_XOR : rd <= rs1 ^ rs2;
			`ALU_OP_SRL : rd <= rs1 >> shamt;
			`ALU_OP_OR  : rd <= rs1 | rs2;
			`ALU_OP_AND : rd <= rs1 & rs2;
			`ALU_OP_SUB : rd <= rs1 - rs2;
			`ALU_OP_SRA : rd <= $signed(rs1) >>> shamt;
			`ALU_OP_SLLW: rd <= {`W_LEN'b0,rs1W << shamt};
			`ALU_OP_SRLW: rd <= {`W_LEN'b0,rs1W >> shamt};
			`ALU_OP_SRAW: rd <= {`W_LEN'b0,$signed(rs1W) >>> shamt};

			default: rd <=0;
		endcase
	else
		rd <= 0;
end

endmodule
