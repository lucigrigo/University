function [NC points] = read_input_data(file_params, file_points)
	% citirea numarului de centroizi si a punctelor
	file1 = fopen(file_params, "r");
	NC = fscanf(file1, "%d");
	points = [];
	load(file_points, 'points');
	fclose(file1);
end
