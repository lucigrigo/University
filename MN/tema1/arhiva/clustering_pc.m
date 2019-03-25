function centroids = clustering_pc(points, NC)
	# initializarea centroizilor cu valori random din punctele citite
	centroids = zeros(NC, size(NC,2));
	centroids = points(randperm(size(NC,1))(1:NC), :);
end
