function [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img)
  % pasul 6
  test_img = double(rgb2gray(imread(image_path)));
  test_img = transpose(test_img);
  test_img_vect = test_img(:);
  test_img_vect = test_img_vect - m;
  % pasul 7
  PrTestImg = transpose(eigenfaces) * test_img_vect;
  % pasul 8
  output_img_index = -1;
  min_dist = Inf;
  for i=1:size(pr_img, 2)
    if norm(PrTestImg - pr_img(:, i)) < min_dist
      min_dist = norm(PrTestImg - pr_img(:, i));
      output_img_index = i;
    end
  end 
end