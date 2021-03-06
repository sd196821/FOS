`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:23:56 10/01/2015 
// Design Name: 
// Module Name:    MPU (Math Processing Unit)
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
`include "BEAN"
`define 
module MPU(
				input [`MPU_OP_WIDTH-1:0] op,
				input [`S_LEN-1:0] rs1,
				input [`S_LEN-1:0] rs2,
				output reg [`S_LEN - 1:0] rdh,
				output reg [`S_LEN - 1:0] rdl,
				input clk,
				input enable,
				output reg[1:0] avlb,
				);


endmodule
