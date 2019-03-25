function [NC points] = read_input_data(file_params, file_points)
	file1 = fopen(file_params, "r");	

	NC = fscanf(file1, "%d");
	points = [];

	load(file_points, 'points');
	view_points(points);

	fclose(file1);
end