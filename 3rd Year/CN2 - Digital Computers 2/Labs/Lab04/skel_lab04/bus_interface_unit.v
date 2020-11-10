`include "defines.vh"
module bus_interface_unit #(
		parameter MEM_START_ADDR = 8'h40,
		parameter MEM_STOP_ADDR  = 8'hBF,
		parameter DATA_WIDTH     = 8,    // registers are 8 bits in width
		parameter ADDR_WIDTH     = 16    // 64KB address space
	)(
		input  wire  [`GROUP_COUNT-1:0] opcode_group,
		input  wire              [11:0] opcode_imd,
		input  wire [`SIGNAL_COUNT-1:0] signals,
		input  wire    [DATA_WIDTH-1:0] data_to_store,
		input  wire    [ADDR_WIDTH-1:0] indirect_addr,
		output wire    [ADDR_WIDTH-1:0] bus_addr,
		inout  wire    [DATA_WIDTH-1:0] bus_data,
		output wire                     mem_cs,
		output wire                     mem_we,
		output wire                     mem_oe
	);

	wire [ADDR_WIDTH-1:0] internal_mem_addr;
	wire                  mem_access, io_access;
	wire                  mem_addr_is_in_mem;
	wire                  uses_indirect;
	wire                  should_store;
	wire                  should_load;

	assign should_load = signals[`CONTROL_MEM_READ];
	assign should_store = signals[`CONTROL_MEM_WRITE];
	assign uses_indirect =
		(opcode_group[`GROUP_LOAD_INDIRECT] ||
		 opcode_group[`GROUP_STORE_INDIRECT]);
	assign mem_access = signals[`CONTROL_MEM_READ] ||
						signals[`CONTROL_MEM_WRITE];
	assign mem_addr_is_in_mem = mem_access &&
			(internal_mem_addr >= MEM_START_ADDR &&
			 internal_mem_addr <= MEM_STOP_ADDR);

	/* Indirect mem access. Stack operations: push, pop. */
	assign internal_mem_addr =
		uses_indirect ?
			indirect_addr :
			{4'b0, opcode_imd};

	assign mem_cs = mem_addr_is_in_mem;
	assign mem_we = (mem_cs && signals[`CONTROL_MEM_WRITE]) ? 1'b1 :
						 (mem_cs && signals[`CONTROL_MEM_READ])  ? 1'b0 : 1'bx;
	assign mem_oe = (mem_cs && signals[`CONTROL_MEM_READ])  ? 1'b1 :
						 (mem_cs && signals[`CONTROL_MEM_WRITE]) ? 1'b0 : 1'bx;

	/* logic for io operations.
	 * Hint: check defines.vh */
	/* TODO: Cititi si intelegeti cum sunt setate bus_addr si bus_data */
	assign bus_addr = mem_cs ? internal_mem_addr - MEM_START_ADDR :
					  {ADDR_WIDTH{1'bx}};

	assign bus_data = should_store ? data_to_store : {DATA_WIDTH{1'bz}};

endmodule
