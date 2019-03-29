function centroids = clustering_pc(points, NC)
	% initializarea centroizilor cu valori random din punctele citite si a celor-
	% lalte variabile
	randomIndices = randperm(length(points), NC);
	centroids = points(randomIndices, :);
	pointsNumber = size(points, 1);
	groupIndices = zeros(size(points));
	localCentroids = centroids;
	% realizarea iteratiilor din cadrul algoritmului pana la fixarea centroizilor
	% in localCentroids modific mereu centroizii, iar in centroids ii pastrez pe
	% cei din pasiul precedenti
	% cand cele doua variabile au aceleasi valori, algoritmul nu se mai itereaza
	do
		centroids = localCentroids;
		groupIndices = zeros(size(points),1);
		% atribuirea fiecarui punct centroidului cel mai apropiat
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
		% recalcularea centroizilor ca centre de masa ale grupurilor aferente
		for i=1:NC
			specificPoints = [];
			specificPoints = points(groupIndices==i,:);
			% am lasat if-ul asta aici in cazul in care dintr-un motiv anume, unui
			% centroid nu ii este asociat niciun punct
			if ~specificPoints
				break;
			end
			localCentroids(i,:) = mean(specificPoints());
		end
	% conditia de oprire pentru algoritm
	until localCentroids==centroids;
	centroids = localCentroids;
end
