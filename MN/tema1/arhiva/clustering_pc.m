function centroids = clustering_pc(points, NC)
	# initializarea centroizilor cu valori random din punctele citite
	randomIndices = randperm(length(points), NC);
	centroids = points(randomIndices, :);
	pointsNumber = size(points, 1);
	groupIndices = zeros(size(points));
	localCentroids = centroids;
	# realizarea iteratiilor din cadrul algoritmului
	do
		# atribuirea fiecarui punct centroidului cel mai apropiat
		centroids = localCentroids;
		groupIndices = zeros(size(points),1);
		for i=1:pointsNumber
			minDistance = norm(points(i,:) - localCentroids(1,:));
			j = 1;
			for k=1:NC
				dist = norm(points(i,:) - localCentroids(k,:));
				if dist < minDistance
					minDistance = dist;
					j = k;
				end
			end
			groupIndices(i) = j;
		end
		# recalcularea centroizilor ca centre de masa ale grupurilor aferente
		for i=1:NC
			specificPoints = [];
			specificPoints = points(groupIndices==i,:);
			if ~specificPoints
				break;
			end 
			localCentroids(i,:) = mean(specificPoints());
		end
	until localCentroids==centroids;
	centroids = localCentroids;
end
