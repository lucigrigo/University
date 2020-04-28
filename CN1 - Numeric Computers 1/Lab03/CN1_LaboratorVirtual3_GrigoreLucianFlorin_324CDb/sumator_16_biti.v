`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2020 06:49:39 PM
// Design Name: 
// Module Name: sumator_16_biti
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


module sumator_16_biti(
    input[15:0] a, b,
    input cin,
    output [15:0] result,
    output reg GP, GG, cout
    );
    
    wire P0, P1, P2, P3;
    wire G0, G1, G2, G3;
    reg C1, C2, C3;
    
    sumator_4_biti b0_3(a[3:0],     b[3:0],   cin, result[3:0],   P0, G0);
    sumator_4_biti b4_7(a[7:4],     b[7:4],   C1,  result[7:4],   P1, G1);
    sumator_4_biti b8_11(a[11:8],   b[11:8],  C2,  result[11:8],  P2, G2);
    sumator_4_biti b12_15(a[15:12], b[15:12], C3,  result[15:12], P3, G3);
    
    
    always @(a or b or cin or P0 or P1 or P2 or P3 or G0 or G1 or G2 or G3)
    begin
        C1 = G0 | (P0 & cin);
        C2 = G1 | (P1 & G0) | (P1 & P0 & cin);
        C3 = G2 | (P2 & G1) | (P2 & P1 & G0) | (P2 & P1 & P0 & cin);
        
        cout = G3 | (P3 & G2) | (P3 & P2 & G1) | (P3 & P2 & P1 & G0) | (P3 & P2 & P1 & P0 & cin); 
        
        GP = P3 & P2 & P1 & P0;
        GG = G3 | (P3 & G2) | (P3 & P2 & G1) | (P3 & P2 & P1 & G0);
    end
    
    
endmodule
