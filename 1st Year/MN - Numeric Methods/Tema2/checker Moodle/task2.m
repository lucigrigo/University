% Tema 2 - Metode Numerice
% Grigore Lucian-Florin 314CD
function task2()
   % desenarea primului grafic
   figure(1);
   A = double(imread('./in/images/image3.gif'));
   v = svd(A);
   plot(v);
   % desenarea celui de-al doilea grafic
   figure(2);
   nr_k = 130;
   A = double(imread('./in/images/image3.gif'));
   v = svd(A);
   info = [];
   for k=1:nr_k
      info(k) = (sum(v(1:k)) / sum(v(1:nr_k)));
   end
   plot(info);
   % desenarea celui de-al treilea grafic
   figure(3);
   nr_k = 130;
   A = double(imread('./in/images/image3.gif'));
   err_aprox = [];
   for k=1:nr_k
      A_k = task1('./in/images/image3.gif', k);
      m = size(A_k, 1);
      n = size(A_k, 2);
      err_aprox_temp = 0;
      for i=1:m
         for j=1:n
            temp = ((A(i, j) - A_k(i, j)) ^ 2);
            err_aprox_temp = err_aprox_temp + temp;
         end
      end
      err_aprox_temp /= (m * n);
      err_aprox(k) = err_aprox_temp;
   end
   plot(err_aprox);
   % desenarea celui de-al patrulea grafic
   figure(4);
   nr_k = 130;
   A_k = task1('./in/images/image3.gif', nr_k);
   [m, n] = size(A_k);
   comp_rate = [];
   for k=1:nr_k
      comp_rate(k) = ((m * k + n * k + k) / (m * n));
   end
   plot(comp_rate);
end
