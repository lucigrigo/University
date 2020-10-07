%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                    Tema 1 Metode Numerice, 2019                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  NU MODIFICATI acest fisier, el va fi inlocuit la testare cu continutul  %
% initial. Fiecare functie trebuie implementata in fisierul corespunzator. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test task 4 specifically
function pass = test_cost_by_index(file_index)
	
	% set parameters
	pass = 1;
	epsilon = 1e-5;

	% set file names
	file_params = strcat("cls/cluster_", num2str(file_index), ".param");
	file_points = strcat("cls/cluster_", num2str(file_index), ".points");
	file_out = strcat("out/cluster_", num2str(file_index), ".out");

	% call user function
	cost_out = compute_cost(file_params, file_points);

	% check for Inf
	if cost_out == Inf
		printf("Infinite result: 'cost'. Maybe the function has not been implemented?\n");
		pass = 0;
		return
	end

	% load correct output
	load(file_out);

	% check
	if abs(cost_out - cost_ok) > epsilon
		pass = 0;
		printf("Wrong cost.\n");
	end
end

