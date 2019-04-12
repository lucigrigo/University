function [A_k S] = task3(image, k)
  A = double(imread(image));
  miu = []; 
  m = size(A, 1);
  n = size(A, 2);
  % pasul 1
  for i=1:m
    temp_miu = 0;
    for j=1:n
       temp_miu += A(i, j);
    end
		temp_miu /= n;
    miu(i) = temp_miu;
  end
  % pasul 2
  for i=1:m
    A(i, :) = A(i, :) .- miu(i);
  end
  % pasul 3
  Z = (transpose(A) / sqrt(n - 1));
  % pasul 4
  [U, S, V] = svd(Z);
  % pasul 5
  W = V(:, 1:k);
  % pasul 6
  Y = transpose(W) * A;
  % pasul 7
  A_k = W * Y;
	miu = transpose(miu);
	for i=1:size(A, 1) 
		A_k(i, :) += miu(i);
	end 
endfunction