`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2020 06:47:31 PM
// Design Name: 
// Module Name: sumator_1_bit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sumator_1_bit(
    input a, b, cin,
    output reg p, g, sum
    );
    
    always @(a or b or cin)
    begin
        p = a | b;
        g = a & b;
        sum = (a^b)^cin;
        
    end
       
endmodule

