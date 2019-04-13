function [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img)
  % pasul 6
  test_img = double(rgb2gray(imread(image_path)));
  test_img_vect = [];
  for i=1:size(test_img, 1)
    line = transpose(test_img(i, :));
    test_img_vect = vertcat(test_img_vect, line);
  end 
  med = mean(test_img_vect);
  test_img_vect -= med;
  % pasul 7
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