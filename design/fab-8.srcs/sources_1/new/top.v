module top();

	reg[7:0] registers[0:15];

	reg[23:0] instruction;

	always @(posedge clk) begin
		if(instruction[0:7] == ADD) begin
			registers[instruction[8:11]] = 
		end
	end


endmodule
