`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:15:11 10/02/2015 
// Design Name: 
// Module Name:    REG 
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
`define	REG_IO_CHANNEL		2
`define	REG_CHANNEL_WIDTH	2
`define	REG_CHANNEL_DEPTH	5	
`define	REG_DEPTH			`REG_CHANNEL_WIDTH+`REG_CHANNEL_DEPTH			
`define 	REG_CHANNEL_X		0
`define	REG_CHANNEL_F		1
`define	REG_CHANNEL_I		2

module REG(
				input  [(`REG_DEPTH*`REG_IO_CHANNEL)-1:0] selcet_rs1,
				input  [(`REG_DEPTH*`REG_IO_CHANNEL)-1:0] selcet_rs2,
				input  [(`REG_DEPTH*`REG_IO_CHANNEL)-1:0] selcet_rs3,
				input  [(`REG_DEPTH*`REG_IO_CHANNEL)-1:0] selcet_rd,
				input	 [(`X_LEN*`REG_IO_CHANNEL)-1:0] 		rd_data,
				output reg [(`X_LEN*`REG_IO_CHANNEL)-1:0] rs1_data,
				output reg [(`X_LEN*`REG_IO_CHANNEL)-1:0] rs2_data,
				output reg [(`X_LEN*`REG_IO_CHANNEL)-1:0] rs3_data,
				output reg [1:0]finish,
				input 												clk,
				output 												error
				);
reg [`X_LEN-1:0] register [`REG_CHANNEL_WIDTH-1:0][`REG_CHANNEL_DEPTH-1:0];

wire [`REG_CHANNEL_WIDTH-1:0] cw1 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_DEPTH-1:0] cd1 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_WIDTH-1:0] cw2 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_DEPTH-1:0] cd2 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_WIDTH-1:0] cw3 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_DEPTH-1:0] cd3 [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_WIDTH-1:0] cwd [`REG_IO_CHANNEL-1:0];
wire [`REG_CHANNEL_DEPTH-1:0] cdd [`REG_IO_CHANNEL-1:0];

genvar i;
generate 
	for(i = 0; i < `REG_IO_CHANNEL;i = i + 1)
	begin:bit
		assign cw1[i][`REG_CHANNEL_WIDTH-1:0] = selcet_rs1[(i+1)*`REG_DEPTH:i*`REG_DEPTH+`REG_CHANNEL_DEPTH];
		assign cd1[i][`REG_CHANNEL_DEPTH-1:0] = selcet_rs1[(i+1)*`REG_DEPTH-`REG_CHANNEL_WIDTH:i*`REG_DEPTH];
		assign cw2[i][`REG_CHANNEL_WIDTH-1:0] = selcet_rs2[(i+1)*`REG_DEPTH:i*`REG_DEPTH+`REG_CHANNEL_DEPTH];
		assign cd2[i][`REG_CHANNEL_DEPTH-1:0] = selcet_rs2[(i+1)*`REG_DEPTH-`REG_CHANNEL_WIDTH:i*`REG_DEPTH];		
		assign cw3[i][`REG_CHANNEL_WIDTH-1:0] = selcet_rs3[(i+1)*`REG_DEPTH:i*`REG_DEPTH+`REG_CHANNEL_DEPTH];
		assign cd3[i][`REG_CHANNEL_DEPTH-1:0] = selcet_rs3[(i+1)*`REG_DEPTH-`REG_CHANNEL_WIDTH:i*`REG_DEPTH];
		assign cwd[i][`REG_CHANNEL_WIDTH-1:0] = selcet_rd[(i+1)*`REG_DEPTH:i*`REG_DEPTH+`REG_CHANNEL_DEPTH];
		assign cdd[i][`REG_CHANNEL_DEPTH-1:0] = selcet_rd[(i+1)*`REG_DEPTH-`REG_CHANNEL_WIDTH:i*`REG_DEPTH];
		
		always@(posedge clk)
		begin
			rs1_data[i] <= register[cw1[i]][cd1[i]];
			rs2_data[i] <= register[cw2[i]][cd2[i]];
			rs3_data[i] <= register[cw3[i]][cd3[i]];
			register[cwd[i]][cdd[i]] <= rd_data[(i+1)*`X_LEN-1:i*`X_LEN];
		end
	end
endgenerate

endmodule
