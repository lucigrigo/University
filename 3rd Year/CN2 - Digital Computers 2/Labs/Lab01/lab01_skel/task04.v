module task04 (
        input  wire clk,        // clock
        input  wire rst,        // reset
        input  wire [3:0] address,
        output wire [7:0] data
    );
 
	reg [1:0]  state;
	reg [1:0]  next_state;
	
	/* Memory params */
	reg we, oe, cs;
	
	// TODO: Define other required params
	
 
	localparam TRUE = 1'b1,
				  FALSE = 1'b0,
				  STATE_IDLE = 2'd0,
				  STATE_SRAM_READ_INIT = 2'b01,
				  STATE_SRAM_READ = 2'b10;
 
	// TODO: Implement transition from state to next state
	always @(clk) begin
		if (rst)
			state <= 1'dx; 
		else
			state <= 1'dx;
	end
 
	// TODO: Implement the process of reading/writing data
	//                 how to change the state
	// Hint: Pay attention to the list of signals which trigger the block.
	//       When do we want it to run?
	always @(*) begin
		case (state)
			STATE_IDLE: begin
			
			end
			STATE_SRAM_READ_INIT: begin
			
			end
			STATE_SRAM_READ: begin
			
			end
		endcase
	end
	
	// TODO: Assign a value to data bus
	assign data = 1'dx;
	
	// TODO: Create an instance for each memory module
	// Hint: Pay attention to the address width

endmodule