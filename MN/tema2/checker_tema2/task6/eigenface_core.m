function [m A eigenfaces pr_img] = eigenface_core(database_path)
  % pasul 1
  T = [];
  for i=1:10
    temp_image = double(rgb2gray(imread(sprintf('./dataset/%d.jpg', i))));
    vect_images = [];
    for k=1:size(temp_image, 1)
      line = transpose(temp_image(k, :));
      vect_images = vertcat(vect_images, line);
    end 
    T = horzcat(T, vect_images);
    % T = vertcat(T, vect_images);
  end 
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
  m = transpose(m);
  A = T - m;  
  % pasul 4
  [U, S, V] = svd((transpose(A) * A));
  % [V D] = eig((transpose(A) * A));
  V_final = [];
  for i=1:size(S, 1)
  % for i=1:size(D, 1)
    if S(i, i) > 1
      V_final = horzcat(V_final, V(:, i)); 
    endif
  end
  % eigenfaces = A * V_final;
  eigenfaces = A * V;
  % pasul 5
  pr_img = transpose(eigenfaces) * A;
end