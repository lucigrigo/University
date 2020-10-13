(module task01a(
	output out,
	input in0,
	input in1,
	input in2,
	input in3
);

	wire rez1, rez2, rez3, rez4, rez5, rez6;
	or or1(rez1, in1, in2);
	nand nand1(rez2, in3, rez1);
	not not1(rez3, in0);
	or or2(rez4, in1, in3);
	and and1(rez5, rez4, rez3);
	and and2(out, rez6, rez2);

endmodule
)