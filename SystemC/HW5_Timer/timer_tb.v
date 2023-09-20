`timescale 1ns / 1ns
//`include "mux_case.v"

module timer_tb;
parameter CYCLE = 10;
reg clock, start, timeout;

timer my_timer(
			   .clock(clock),
			   .start(start),
			   .timeout(timeout)
			   );

initial begin
	clock = 1;
	forever #(CYCLE/2) clock = ~clock;
end

initial begin
	fork 
		#0 start = 1'b1;
		#30 start = 1'b0;		
		#60 start = 1'b1;
		#70 start = 1'b0;	
		#190 start = 1'b1;
		#200 start = 1'b0;
		#300 $finish;
	join
end

initial begin
	$fsdbDumpfile("timer.fsdb");
	$fsdbDumpvars();
end

endmodule
