function view_cost_vs_nc(file_points)
	% declararea si citirea punctelor, declararea vectorului cu costuri
	points = [];
	load(file_points, 'points');
	costs = zeros(10,1);
	% setari ale graficului
	hold on;
	grid on;
	xlabel('cluster number');
	ylabel('cost');
	% realizarea costurilor prin apelarea functiilor de la task-urile trecute
	for i=1:10
		centroids = clustering_pc(points,i);
		cost = compute_cost_pc(points,centroids);
		costs(i) = cost;
	end
	% desenarea graficului
	plot(costs);
end
