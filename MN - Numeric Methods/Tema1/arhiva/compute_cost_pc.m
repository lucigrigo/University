function cost = compute_cost_pc(points, centroids)
	% declararea variabilelor pentru: costul total, numarului de puncte, numaru-
	% lui de centroizi si a vectorului de indici pentru centroidul de care apar-
	% tine fiecare punct
	cost = 0;
	pointsNumber = size(points, 1);
	NC = size(centroids, 1);
	groupIndices = zeros(size(points));
	% impartirea punctelor in functie de centroizii de care sunt cel mai apropiati
	for i=1:pointsNumber
		minDistance = norm(points(i,:) - centroids(1,:));
		j = 1;
		for k=1:NC
			dist = norm(points(i,:) - centroids(k,:));
			if dist < minDistance
				minDistance = dist;
				j = k;
			end
		end
		groupIndices(i) = j;
	end
	% calcularea costului total ca suma de distante pentru fiecare punct pana la
	% centroidul de care apartin
	for i=1:pointsNumber
		cost += norm(points(i,:) - centroids(groupIndices(i),:));
	end
end
