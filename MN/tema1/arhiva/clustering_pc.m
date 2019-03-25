function centroids = clustering_pc(points, NC)

	# initializarea centroizilor cu valori random din punctele citite
	randomIndices = sort(randperm(length(points), NC));
	centroids = points(randomIndices, :);
	pointsNumber = size(points, 1);
	groupIndices = zeros(size(points));
	max_iterations = 50;

	for p=1:max_iterations
		# atribuirea fiecarui punct unui grup in jurul celui mai apropiat centroid
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
		# recalcularea centroizilor ca centre de masa ale grupurilor aferente
		for i=1:NC
			specificPoints = points(groupIndices==i,:);
			specificPointsNumber = size(specificPoints,1);
			if specificPoints
				centroids(i,:) = [sum(specificPoints(:,1)) sum(specificPoints(:,2)) sum(specificPoints(:,3))] * (1 / specificPointsNumber);
			else
				break;
			end
		end
	end
	#printf("%.15f %.15f %.15f\n", centroids(2,1), centroids(2,2), centroids(2,3));
	#printf("%.15f %.15f %.15f\n", centroids(1,1), centroids(1,2), centroids(1,3));
	#view_points(centroids);
end
