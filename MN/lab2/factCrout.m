function [L, U] = factCrout()
  ptr = fopen("val.txt", "r");
  n = fscanf(ptr, "%d", 1);
  L = zeros(n, n);
  U = eye(n, n);
  A = zeros(n, n);
  k=0;

  for i = 1:n
      for j = 1:n
          [A(i, j), k] = fscanf(ptr, "%d", 1);
      endfor
  endfor

  printf("\tMatricea initiala:\n");
  disp(A)
  printf("\n");

  for p = 1 : n
    for i = p : n
      s = 0;
      for k = 1 : p-1
        s = s + L(i, k) * U(k, p);
      endfor
      L(i, p) = A(i, p) - s;
    endfor
    for j = p + 1 : n
      s = 0;
      for k = 1 : p-1
        s = s + L(p, k) * U(k, j);
      endfor
      U(p, j) = (A(p, j) - s) / L(p, p);
    endfor
 endfor

  fclose(ptr);
endfunction
