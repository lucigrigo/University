function [m A eigenfaces pr_img] = eigenface_core(database_path)
  % pasul 1
  for i=1:10
    temp_image = double(rgb2gray(imread(sprintf('./dataset/%0d.jpg', i))));
    vect_images(:, i) = temp_image(:);
  end 
  T = horzcat(vect_images(:, 1), vect_images(:, 2), vect_images(:, 3), vect_images(:, 4),
    vect_images(:, 5), vect_images(:, 6), vect_images(:, 7),vect_images(:, 8), vect_images(:, 9), vect_images(:, 10));
  % pasul 2
  m = [];
  for i=1:size(T, 1)
    med = 0;
    for j=1:size(T, 2)
      med += T(i, j);
    end 
    med /= size(T, 2);
    m(i) = med;
  end
  A = T - transpose(m);  
  m = transpose(m);
  % pasul 4
  % [U, S, V] = svd((transpose(A) * A));
  [V D] = eig((transpose(A) * A));
  V_final = [];
  % for i=1:size(S, 1)
  for i=1:size(D, 1)
    if D(i, i) > 1
      V_final = horzcat(V_final, V(:, i)); 
    endif
  end
  eigenfaces = A * V;
  % pasul 5
  pr_img = transpose(eigenfaces) * A;
end