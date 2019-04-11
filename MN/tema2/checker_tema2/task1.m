function A_k = task1(image, k)
  A_k = double(imread(image));
  [U,S,V] = svd(A_k);
  U = U(:, 1:k);
  S = S(1:k, 1:k);
  V = transpose(V);
  V = V(1:k, :);
  A_k = U * S * V;
end