`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2020 05:56:13 PM
// Design Name: 
// Module Name: sumator_4_biti
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


module sumator_4_biti(
    input[3:0] a, b,
    input cin,
    output [3:0] sum,
    output reg P, G
    );
    
    reg c1, c2, c3;
    wire p0, p1, p2, p3;
    wire g0, g1, g2, g3;
    
    sumator_1_bit b0(a[0], b[0], cin, p0, g0, sum[0]);
    sumator_1_bit b1(a[1], b[1], c1,  p1, g1, sum[1]);
    sumator_1_bit b2(a[2], b[2], c2,  p2, g2, sum[2]);
    sumator_1_bit b3(a[3], b[3], c3,  p3, g3, sum[3]);
        
    always @(a or b or cin or p0 or p1 or p2 or p3 or g0 or g1 or g2 or g3)
    begin
        c1 = g0 | (p0 & cin);
        c2 = g1 | (p1 & g0) | (p1 & p0 & cin);
        c3 = g2 | (p2 & g1) | (p2 & p1 & g0) | (p2 & p1 & p0 & cin);
        
        P = p3 & p2 & p1 & p0;
        G = g3 | (p3 & g2) | (p3 & p2 & g1) | (p3 & p2 & p1 & g0);
    end
    
endmodule
