function view_clusters(points, centroids)
	pointsNumber = size(points, 1);
	NC = size(centroids, 1);
	groupIndices = zeros(size(points));

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

	#colorsArray

	#for i=1:pointsNumber
		scatter3([points(:, 1)], [points(:, 2)], [points(:, 3)], 'm', 'filled');
	#end
end
