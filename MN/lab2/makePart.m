function makePart() ptr = fopen("val2.txt", "r");
n = fscanf(ptr, "%d", 1);
A = zeros(n, n);
k = 0;

  for i = 1:n
      for j = 1:n
          [A(i, j), k] = fscanf(ptr, "%d", 1);
  endfor endfor

      printf("\tMatricea initiala:\n");
  disp(A) printf("\n");

  A1 = ones(1, 1);
  A2 = ones(3, 1);
  A3 = ones(1, 3);
  A4 = ones(3, 3);

  A1(1, 1) = A(1, 1);
  A2(1, 1) = A(2, 1);
  A2(2, 1) = A(3, 1);
  A2(3, 1) = A(4, 1);
  A3(1, 1) = A(1, 2);
  A3(1, 2) = A(1, 3);
  A3(1, 3) = A(1, 4);
  for i = 1:3
    for j = 1:3
      A4(i, j) = A(i + 1, j + 1);
  endfor endfor

      X1 = zeros(1, 1);
  X2 = zeros(3, 1);
  X3 = zeros(1, 3);
  X4 = zeros(3, 3);

  X1 = inv(A1 - A3 * inv(A4) * A2);
  X2 = (-1) * inv(A4) * A2 * X1;
  X4 = inv(A4 - A2 * inv(A1) * A3);
  X3 = (-1) * inv(A1) * A3 * X4;

  X = ones(n, n);
  X(1, 1) = X1(1, 1);
  X(1, 2) = X3(1, 1);
  X(1, 3) = X3(1, 2);
  X(1, 4) = X3(1, 3);
  X(2, 1) = X2(1, 1);
  X(3, 1) = X2(2, 1);
  X(4, 1) = X2(3, 1);
  for i = 1:3
    for j = 1:3
        X(i + 1, j + 1) = X4(i, j);
  endfor endfor

      printf("\tMatricea finala:\n");
  disp(X) printf("\n\n");
  fclose(ptr);
  endfunction
