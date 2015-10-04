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
module Decoder(
					input [XPR_LEN-1:0] Channel [DECODER_CHANNEL_DEPTH-1:0];
					output reg[CECODER_CHANNEL_DEPTH-1:0] isempty;
					input drop;
					output 
					);


endmodule
