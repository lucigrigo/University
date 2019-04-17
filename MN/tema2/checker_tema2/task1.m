% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function A_k = task1(image, k)
  % citirea imaginii
  A_k = double(imread(image));
  % apelez functia SVD pentru a obtine matricile U, S si V
  [U,S,V] = svd(A_k);
  % alegerea primelor k linii / coloane corespunzator cerintei
  U = U(:, 1:k);
  S = S(1:k, 1:k);
  V = transpose(V);
  V = V(1:k, :);
  % obtinerea matricii finale
  A_k = U * S * V;
end
