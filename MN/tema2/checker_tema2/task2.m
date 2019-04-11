function task2()
   % desenarea primului grafic
   figure(1);
   A = double(imread('./in/images/image2.gif'));
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
   % figure(3);
   % nr_k = 200;
   % A_k = task1('./in/images/image1.gif', nr_k);
   % A = double(imread('./in/images/image1.gif'));
   % err_aprox = [];
   % m = size(A_k, 1);
   % n = size(A_k, 2);
   % for k=1:nr_k
   %    err_aprox_temp = 0;
   %    for i=1:m
   %       for j=1:n
   %          err_aprox_temp += ((A(i, j) - A_k(i, j)) ^ 2);
   %       end
   %    end
   %    err_aprox_temp /= (m * n);
   %    err_aprox(k) = err_aprox_temp;
   % end
   % plot(err_aprox);

   % desenarea celui de-al patrulea grafic
   figure(4);
   A_k = task1('./in/images/image4.gif', nr_k);
   nr_k = 180;
   m = size(A_k, 1);
   n = size(A_k, 2);
   comp_rate = [];
   for k=1:nr_k
      comp_rate(k) = ((m * k + n * k + k) / (m * n));
   end 
   plot(comp_rate);
end