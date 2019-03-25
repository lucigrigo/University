%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                    Tema 1 Metode Numerice, 2019                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  NU MODIFICATI acest fisier, el va fi inlocuit la testare cu continutul  %
% initial. Fiecare functie trebuie implementata in fisierul corespunzator. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% this will call user functions to generate plots for tasks 3 and 5
function graph()

	% files
	file_params = "cls/cluster_2.param";
	file_points = "cls/cluster_2.points";

	% call clustering algorithm to compute centroids
	[points centroids] = clustering(file_params, file_points);
	
	% view 3D result
	figure(1)
	clf
	view_clusters(points, centroids);

	% draw cost(NC) function
	figure(2)
	clf
	view_cost_vs_nc(file_points);
end

