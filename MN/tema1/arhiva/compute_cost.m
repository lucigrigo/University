% You DO NOT need to modify this file.
% reads input data from files, computes centroids and returns the cost 
% of the clustering solution
function cost = compute_cost(file_params, file_points)
	[points centroids] = clustering(file_params, file_points);
	if length(centroids) == 0
		cost = Inf; 
	else
		cost = compute_cost_pc(points, centroids);
	end
end

