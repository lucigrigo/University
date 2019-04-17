% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function [min_dist output_img_index] = face_recognition(image_path, m,
                      A, eigenfaces, pr_img)
  % citirea imaginii de test
  test_img = double(rgb2gray(imread(image_path)));
  % transformarea imaginii de test intr-un vector coloana
  test_img = transpose(test_img);
  test_img_vect = test_img(:);
  % extragerea mediei din imaginea de test
  test_img_vect = test_img_vect - m;
  % calcularea proiectiei imaginii de test in spatiul fetelor
  PrTestImg = transpose(eigenfaces) * test_img_vect;
  % calcularea celei mai mici distante dintre proiectia imaginii de test
  % si proiectiile calculate anterior
  output_img_index = -1;
  min_dist = Inf;
  for i=1:size(pr_img, 2)
    if norm(PrTestImg - pr_img(:, i)) < min_dist
      min_dist = norm(PrTestImg - pr_img(:, i));
      output_img_index = i;
    end
  end
end
