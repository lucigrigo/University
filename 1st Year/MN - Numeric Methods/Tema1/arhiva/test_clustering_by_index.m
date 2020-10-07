%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                    Tema 1 Metode Numerice, 2019                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  NU MODIFICATI acest fisier, el va fi inlocuit la testare cu continutul  %
% initial. Fiecare functie trebuie implementata in fisierul corespunzator. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test task 2 specifically
function pass = test_clustering_by_index(file_index)
	
	% set parameters
	epsilon = 1e-5;
	pass = 1;

	% set file names
	file_params = strcat("cls/cluster_", num2str(file_index), ".param");
	file_points = strcat("cls/cluster_", num2str(file_index), ".points");
	file_out = strcat("out/cluster_", num2str(file_index), ".out");

	% call user function
	[points_out centroids_out] = clustering(file_params, file_points);

	if length(centroids_out) == 0
		pass = 0;
		printf("Empty result: 'centroids'. Maybe the function has not been implemented?\n");
		return;
	end

	% load correct output
	load(file_out);
	
	% check points matrix size
	if length(find(size(points_out) != size(points_ok)))
		pass = 0;
		printf("Incorrect size of matrix 'points'.\n");
		return
	endif

	% check centroids matrix size
	if length(find(size(centroids_out) != size(centroids_ok)))
		pass = 0;
		printf("Incorrect size of matrix 'centroids'.\n");
		return
	endif
	
	% reorder points
	points_out = reorder_by_x(points_out);
	points_ok = reorder_by_x(points_ok);

	% reorder centroids 
	centroids_out = reorder_by_x(centroids_out);
	centroids_ok = reorder_by_x(centroids_ok);

	% substract centroid matrixes and compute max distance
	centroids_diff = centroids_ok - centroids_out;
	points_diff = points_ok - points_out;
	
	% check centroids
	if max(norm(centroids_diff, 2, "rows")) > epsilon
		pass = 0;
		printf("Wrong centroids!\n");
	end

	% check points
	if max(norm(points_diff, 2, "rows")) > epsilon
		pass = 0;
		printf("Points differ from original.\n");
	end
end

