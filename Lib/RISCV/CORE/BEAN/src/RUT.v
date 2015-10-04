`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:18:07 10/04/2015 
// Design Name: 
// Module Name:    RUT 
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
`define REG_NUMBER 32
module RUT(
				input[`REG_NUMBER-1:0] finish,
				input[`REG_NUMBER-1:0] setusing,
				output reg[`REG_NUMBER-1:0] using,
				input clk
    );


always@(posedge clk)
begin
	using <= (using &(~finish))|setusing;
end


endmodule
