`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2020 06:55:04 PM
// Design Name: 
// Module Name: simulare_sumator_16_biti
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


module simulare_sumator_16_biti();

    reg[15:0] a, b;
    reg cin;
    wire[15:0] sum;
    wire cout;
    wire GG;
    wire GP;
    
    sumator_16_biti suma(a, b, cin, sum, GP, GG, cout);
    
    initial
    begin
        #50;
        a = 16;
        b = 15;
        cin = 0;
        #50;
        a = 1001;
        #50;
        a = 1;
        b = 2;
        cin = 1;
        #50;
        a = 64411;
    end

endmodule