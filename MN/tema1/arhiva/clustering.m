% You DO NOT need to modify this file.
% reads input data from files, outputs points and computed centroids
function [points centroids] = clustering(file_params, file_points)
	[NC points] = read_input_data(file_params, file_points);
	centroids = clustering_pc(points, NC);
end

