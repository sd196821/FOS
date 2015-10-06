`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:23:26 10/01/2015 
// Design Name: 
// Module Name:    Decoder 
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
`define DECODER_CHANNEL_DEPTH 4//4*32=128bit

//!CHECK CODE
//FENCE
//FENCE.I
//DECODE TYPE

module Decoder(
					input [XPR_LEN-1:0] Channel [DECODER_CHANNEL_DEPTH-1:0],
					input drop,
					output rs1,
					output rs2,
					output rd,
					output imm,
					output funct
					output unit,
					
					output BTB,
					
					
					
					input clk
					
					);
reg[XPR_LEN-1:0] current;
wire [9:3] d_func7;
wire [4:0] d_rs2;
wire [4:0] d_rs1;
wire [2:0] d_func3;
wire [4:0] d_rd;
wire [6:0] d_opcode;
assign d_opcode = current[6:0]
// R-Type
reg [24:0] rtype;
// I-Type
reg [24:0] itype;
// S-Type
reg [24:0] stype
// SB-TYPE
reg [24:0] sbtype
// U-TYPE
reg [24:0] utype
// UJ-TYPE
reg [24:0] ujtype

always@(posedge clk)
begin
	
end
endmodule
