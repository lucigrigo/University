function [m A eigenfaces pr_img] = eigenface_core(database_path)
  % pasul 1
  T = [];
  for i=1:10
    temp_image = double(rgb2gray(imread(sprintf('./dataset/%d.jpg', i))));
    temp_image = transpose(temp_image);
    vect_images = temp_image(:);
    T = [T, vect_images];
  end 
  % pasul 2
  m = mean(T, 2);
  A = T - m;
  % pasul 4
  [V, D] = eig(((A') * A));
  V_final = [];
  diagonal_vect = diag(D);
  for i=1:size(diagonal_vect)
    if diagonal_vect(i) > 1
      V_final = [V_final, V(:, i)];
    endif
  endfor
  eigenfaces = A * V_final;
  % pasul 5
  pr_img = transpose(eigenfaces) * A;
end