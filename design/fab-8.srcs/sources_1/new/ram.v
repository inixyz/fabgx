module ram(
    output[7:0] data_o,
    input clk,
    input we,
    input[15:0] addr,
    input[7:0] data_i
);

    reg[7:0] memory[0:65536];

    assign data_o = memory[addr];

    always @(posedge clk) if(we) memory[addr] = data_i;

endmodule
