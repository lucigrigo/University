module rom #(
        parameter   DATA_WIDTH = 16,
        parameter   ADDR_WIDTH = 8          // 2 * 1024 bytes of ROM
    )(
        input  wire                  clk,
        input  wire [ADDR_WIDTH-1:0] addr,  // here comes the program counter
        output  reg [DATA_WIDTH-1:0] data   // here goes the instruction
    );

    reg [DATA_WIDTH-1:0] value;

    
    always @* begin
        case (addr)
		  /* TODO 5 : Scrieti niste instructiuni valide.
				Puteti sa folositi exemplele oferite in enunt. Utilizati avrasm.jar pentru
				a converti din cod assembly in cod Verilog (care contine cod masina).
				
				ATENTIE! Pentru a beneficia de mesajele de debug puse in checker
                                va trebuie sa lasati ROM neschimbat!
				
                                P.S. Puteti adauga la sfarsit, incepand cu adresa 16.
			*/
		
		/*	 ldi 	r16, 5 		*/
		0:	value = 16'b1110000000000101;
		
		/*	 ldi 	r17, 15 		*/
		1:		value = 16'b1110000000011111;
		
		/*	 push 	r16 		*/
		2:		value = 16'b1001001100001111;
		
		/*	 push 	r17 		*/
		3:		value = 16'b1001001100011111;
		
		/*	 mov 	r30, r16 		*/
		4:		value = 16'b0010111111100000;
		
		/*	 sub 	r30, r17 		*/
		5:		value = 16'b0001101111100001;
		
		/*	 breq 	gigel_is_done 		*/
		6:		value = 16'b1111000000101001;
		
		/*	 brmi 	r17_is_greater 		*/
		7:		value = 16'b1111000000010010;
		
		/*	 sub 	r16, r17 		*/
		8:		value = 16'b0001101100000001;
		
		/*	 rjmp 	main_loop 		*/
		9:		value = 16'b1100111111111010;
		
		/*	 sub 	r17, r16 		*/
		10:		value = 16'b0001101100010000;
		
		/*	 rjmp 	main_loop 		*/
		11:		value = 16'b1100111111111000;
		
		/*	 push 	r16 		*/
		12:		value = 16'b1001001100001111;
		
		/*	 pop 	r20 		*/
		13:		value = 16'b1001000101001111;
		
		/*	 pop 	r21 		*/
		14:		value = 16'b1001000101011111;
		
		/*	 pop 	r22 		*/
		15:		value = 16'b1001000101101111;
		
		// Primele 10 numere fibonacci in r21
		
		/*	 ldi 	r19, 1 		*/
		16:		value = 16'b1110000000110001;
		/*	 ldi 	r20, 10 		*/
		17:		value = 16'b1110000001001010;
		/*	 ldi 	r21, 1 		*/
		18:		value = 16'b1110000001010001;
		/*	 push 	r21 		*/
		19:		value = 16'b1001001101011111;
		/*	 push 	r21 		*/
		20:		value = 16'b1001001101011111;
		/*	 pop 	r21 		*/
		21:		value = 16'b1001000101011111;
		/*	 pop 	r22 		*/
		22:		value = 16'b1001000101101111;
		/*	 add 	r22, r21 		*/
		23:		value = 16'b0000111101100101;
		/*	 push 	r21 		*/
		24:		value = 16'b1001001101011111;
		/*	 push 	r22 		*/
		25:		value = 16'b1001001101101111;
		/*	 sub 	r20, r19 		*/
		26:		value = 16'b0001101101000011;
		/*	 breq 	outside_loop 		*/
		27:		value = 16'b1111000000001001;
		/*	 rjmp 	loop 		*/
		28:		value = 16'b1100111111111000;
		/*	 pop 	r21 		*/
		29:		value = 16'b1001000101011111;
		/*	 pop 	r22 		*/
		30:		value = 16'b1001000101101111;
		
		default:		value = 16'b0000000000000000;

        endcase
    end

    always @(negedge clk) begin
        data <= value;
    end

endmodule
