function [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img)
  % pasul 6
  test_img = double(rgb2gray(imread(image_path)));
  test_img_vect = test_img(:);
  med = mean(test_img_vect);
  % pasul 7
  size(test_img_vect);
  PrTestImg = transpose(eigenfaces) * test_img_vect;
  % pasul 8
  output_img_index = -1;
  min_dist = Inf;
  PrTestImg = transpose(PrTestImg);
  for i=1:size(pr_img, 1)
    if norm(PrTestImg - pr_img(i, :)) < min_dist
      min_dist = norm(PrTestImg - pr_img(i, :));
      output_img_index = i;
    endif
  end 
end