module task01b(
	output out,
	input in0,
	input in1,
	input in2,
	input in3
);

	assign out = (!(in3 & (in1 | in2))) & ((!in0) & (in1 | in3));

endmodule
