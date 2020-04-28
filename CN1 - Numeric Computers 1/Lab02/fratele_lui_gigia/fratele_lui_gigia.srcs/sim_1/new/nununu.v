`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/04/2020 10:27:14 AM
// Design Name: 
// Module Name: nununu
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


module nununu();
    reg a, b, cin;
    wire cout, sum;
    reg [8*100:1] linie;
    integer fd, count, status, i_a, i_b, i_cin, i_sum, i_cout, erori;
    
    diszain_wrapper instance1(a, b, cin, cout, sum);
    
    initial begin
        a = 1'bx; b = 1'bx; cin = 1'bx;
        fd = $fopen("/home/student1/Downloads/lab2/fratele_lui_gigia/input.txt", "r");
        if(fd == 0)
            // do nothing
         count = 1;
         #100
         erori = 0;
         while($fgets(linie, fd))
         begin
            status = $sscanf(linie, "%d %d %d %d %d\n", i_a, i_b, i_cin, i_sum, i_cout);
            a = i_a; b = i_b; cin = i_cin;
            #50
            if(i_sum == sum && i_cout == cout)
                $display("sum = %d si cout = %d (%t) ESTE OK, din a = %d, b = %d, cin = %d", sum, cout, $time, a, b, cin);
            else begin
                erori = erori + 1;
                $display("sum = %d si cout = %d (%t) EROARE! S-A OBTINUT sum (gresit) = %d si cout (gresit) = %d, din a = %d, b = %d, cin = %d", i_sum, i_cout, $time, sum, cout, a, b, cin);
             end
             count = count + 1;
        end
        #50 a = 1'bx; b = 1'bx; cin = 1'bx;
        #50 $stop;
        #50 $finish;
    end     

endmodule