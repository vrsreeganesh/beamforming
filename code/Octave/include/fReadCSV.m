function finalmatrix = fReadCSV(filename_string)
	entire_text 			= fileread(filename_string);
	total_num_characters 	= numel(entire_text);
	p1 						= 1;
	p2 						= 1;
	currentry 				= "";
	currline 				= [];
	finalmatrix				= [];

	while(p2 <= total_num_characters)
		
		curr_char = entire_text(p2);

		if(curr_char == ',' || curr_char == "\n")
			curr_entry 	= entire_text(p1:p2-1);
			currline 	= [currline, str2num(curr_entry)];

			if (curr_char == "\n")
				finalmatrix = [finalmatrix; currline];
				currline 	= [];
			end

			p1 = p2 + 1;
		end
		p2 += 1;
	end
end