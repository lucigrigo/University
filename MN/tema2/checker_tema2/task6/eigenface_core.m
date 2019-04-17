% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function [m A eigenfaces pr_img] = eigenface_core(database_path)
  % matricea T va contine toate imaginile pe coloane diferite
  T = [];
  for i=1:10
    % citirea imaginii
    temp_image = double(rgb2gray(imread(sprintf('./dataset/%d.jpg', i))));
    % transformarea imaginii intr-un vector coloana
    temp_image = transpose(temp_image);
    vect_images = temp_image(:);
    T = [T, vect_images];
  end
  % calcularea mediei pe fiecare linie a matricei T
  m = mean(T, 2);
  % actualizarea matricei A
  A = T - m;
  % descompunerea matricii A' * A
  [V, D] = eig(((A') * A));
  % V_final va contine vectorii proprii corespunzatori valorilor prorii
  % mai mari ca 1
  V_final = [];
  % alegerea acestor vectori proprii
  diagonal_vect = diag(D);
  for i=1:size(diagonal_vect)
    if diagonal_vect(i) > 1
      V_final = [V_final, V(:, i)];
    endif
  endfor
  % calcularea matricei cu fetele proprii
  eigenfaces = A * V_final;
  % calcularea proiectiei fiecarei imaginii in spatiul fetelor
  pr_img = transpose(eigenfaces) * A;
end
