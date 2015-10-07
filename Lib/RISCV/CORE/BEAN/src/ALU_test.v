`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:42:15 10/07/2015
// Design Name:   ALU
// Module Name:   D:/GIT/FOS/Lib/RISCV/CORE/BEAN/src/ALU_test.v
// Project Name:  BEAN
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ALU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module ALU_test;

	// Inputs
	reg [4:0] op;
	reg [63:0] rs1;
	reg [63:0] rs2;
	reg clk;
	reg enable;

	// Outputs
	wire [63:0] rd;

	// Instantiate the Unit Under Test (UUT)
	ALU uut (
		.op(op), 
		.rs1(rs1), 
		.rs2(rs2), 
		.rd(rd), 
		.clk(clk), 
		.enable(enable)
	);

	initial begin
		// Initialize Inputs
		op = 0;
		rs1 = 64'hCCCCCCCCCCCCCCCC;
		rs2 = 64'h5555555555555555;
		clk = 0;
		enable = 1;

		// Wait 100 ns for global reset to finish

		
		#5000;
		$stop;
		// Add stimulus here

	end
   
	always #10 clk = ~clk;
	always #20 op = op+1;
endmodule

