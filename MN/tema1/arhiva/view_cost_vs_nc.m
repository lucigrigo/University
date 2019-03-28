function view_cost_vs_nc(file_points)
	points = [];
	load(file_points, 'points');
	hold on;
	grid on;
	costs = zeros(10,1);
	pointsNumber = size(points,1);
	xlabel('cluster number');
	ylabel('cost');
	for i=1:10
		centroids = clustering_pc(points,i);
		cost = compute_cost_pc(points,centroids);
		costs(i) = cost;
	end 
	plot(costs);
end

