module timer(clock, start, timeout);
input clock;
input start;
output reg timeout;
reg [2:0] count;

// count
always@(posedge clock or posedge start)begin

	if(start)begin
		count <= 3'd5;
	end
	else begin
		if(count == 0) count <= count; 
		else count <= count - 1;
	end
end

// timeout
always@(posedge clock or posedge start)begin

	if(start)begin
		timeout <= 1'b0;
	end
	else begin
		if(count == 0) timeout <= 1'b1;
		else begin
			timeout <= 1'b0;
		end
	end
end

endmodule