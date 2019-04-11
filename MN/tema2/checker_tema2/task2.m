function task2()
   figure(1);
   A = double(imread('./in/images/image2.gif'));
   v = svd(A);
   plot(v);
   figure(2);
   A = task1('./in/images/image2.gif', 150);
   v = diag(A);
   info = (sum(v(1:150)) / sum(v(1:min(size(A, 1), size(A, 2)))));
   % info = sum(v);
   plot(info);
end