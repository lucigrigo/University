% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function [A_k S] = task3(image, k)
  % citirea imaginii
  A = double(imread(image));
  miu = [];
  m = size(A, 1);
  n = size(A, 2);
  % calcularea mediei pe fiecare linie a matricei A
  for i=1:m
    temp_miu = 0;
    for j=1:n
       temp_miu += A(i, j);
    end
		temp_miu /= n;
    miu(i) = temp_miu;
  end
  % actualizarea liniilor matricei A
  for i=1:m
    A(i, :) = A(i, :) - miu(i);
  end
  % construirea matricii Z
  Z = (transpose(A) / sqrt(n - 1));
  % calcularea DVS pentru matricea Z
  [U, S, V] = svd(Z);
  % spatiul k-dimensional al componentelor principale
  W = V(:, 1:k);
  % proiectia lui A in spatiul componentelor principale
  Y = transpose(W) * A;
  % aproximarea matricei initiale
  A_k = W * Y;
	for i=1:size(A, 1)
		A_k(i, :) += miu(i);
	end
endfunction
