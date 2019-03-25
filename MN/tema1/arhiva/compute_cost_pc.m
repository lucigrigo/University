function cost = compute_cost_pc(points, centroids)
	cost = 0;
	pointsNumber = size(points, 1);
	NC = size(centroids, 1);
	groupIndices = ones(size(points));

	for i=1:pointsNumber
		minDistance = norm(points(i) - centroids(1));
		j = 1;
		for k=1:NC
			dist = norm(points(i) - centroids(k));
			if dist < minDistance
				minDist = dist;
				j = k;
			end
		end
		groupIndices(i) = j;
	end

	for i=1:pointsNumber
		cost += norm(points(i) - centroids(groupIndices(i)));
	end
	#printf("~~ %.15f\n", cost);
end
