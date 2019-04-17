% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function [A_k S] = task4(image, k)
  % citirea imaginii
   A = double(imread(image));
   miu = [];
   m = size(A, 1);
   n = size(A, 2);
   % calcularea mediei pe fiecare linie din A
   for i=1:m
      temp_miu = 0;
      for j=1:n
         temp_miu += A(i, j);
      end
      temp_miu /= n;
      miu(i) = temp_miu;
   end
   % actualizarea liniilor din A
   for i=1:m
      A(i, :) = A(i, :) .- miu(i);
   end
   A_k = zeros(k);
   % matricea de covarianta
   Z = (A * transpose(A)) / (n - 1);
   % aplicarea eig
   [V S] = eig(Z);
   % selectarea celor k-coloane din V (spatiul format din componentele princ.)
   W = V(:, 1:k);
   % calcularea proiectiei lui A in spatiul componentelor principale
   Y = transpose(W) * A;
   % aproximarea matricei initiale
   A_k = W * Y;
   miu = transpose(miu);
   for i=1:size(A, 1)
      A_k(i, :) += miu(i);
   end
endfunction
