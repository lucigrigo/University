function view_clusters(points, centroids)
	% declararea variabilelor folosite: numarul de puncte, numarul de clustere si
	% vectorul care face legatura dintre fiecare punct si centroidul de care
	% apartine
	pointsNumber = size(points, 1);
	NC = size(centroids, 1);
	groupIndices = zeros(size(points));
	% impartirea punctelor in functie de centroizii de care apartin
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
	% declararea vectorului de culori (verde, albastru si magenta)
	colorsArray = ['g', 'b', 'm'];
	% setari ale graficului
	hold on;
	grid on;
	view(30,30);
	% colorarea punctelor specifice fiecarui cluster intr-un mod diferit
	for i=1:NC
		specificPoints = points(groupIndices==i,:);
		scatter3(specificPoints(:, 1), specificPoints(:, 2),
				specificPoints(:, 3), [], colorsArray(i), 'filled', 'p');
	end
end
