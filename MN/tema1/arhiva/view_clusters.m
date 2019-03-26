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
				minDistance = dist;
				j = k;
			end
		end
		groupIndices(i) = j;
	end

	colorsArray = [1 1 1; 1 0 1; 1 1 0];
	hold on;
	axis equal;

	#scatter3([points(:, 1)], [points(:, 2)], [points(:, 3)], 'r', 'filled');
	#plot3([points(:, 1)], [points(:, 2)], [points(:, 3)]);

	for i=1:NC
		specificPoints = points(groupIndices==i,:);
		scatter3(specificPoints(:, 1), specificPoints(:, 2), specificPoints(:, 3), [], [colorsArray(1)], 'p');
	end
end
