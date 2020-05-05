function task6()
clc
  clear
  close all
  format long
  pkg load image
  mkdir('./task6/out/');
  database_path = './task6/dataset';
  in_path = strcat(pwd, '/task6/in');
  max_dif = 10*200^3;

  [m, A, eigenfaces pr_img] = eigenface_core(database_path);

  fid = fopen('./task6/out/task6.txt', 'w');
  for i = 1 : 6
    image_path = strcat(in_path,'/',int2str(i),'.jpg');
    
    [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img);
    fprintf(fid, "%f %d\n", round(min_dist), output_img_index);
    
    %decomentati urmatorul if/elseif/else daca doriti sa vedeti imaginile cu fetele recunoscute
    %if (min_dist < max_dif)
        %output_name = strcat(int2str(output_img_index),'.jpg');
        %selected_image = strcat(database_path,'/',output_name);
        %selected_image = imread(selected_image);
	
        %test_image = imread(image_path);

        %figure,imshow(test_image)
        %title('Test Image');
        %figure,imshow(selected_image);
        %title('Equivalent Image');
        
        %msg = strcat(strcat(int2str(i), '.jpg'), ', Matched image is:  ', output_name);
        %disp(msg);
    %elseif (min_dist < max_dif * 5 / 4)
        %printf(strcat(strcat(int2str(i), '.jpg'), ', This image is a human face, but not a known one', '\n'));
    %else
        %printf(strcat(strcat(int2str(i), '.jpg'), ', This image is not a human face', '\n'));
    %end
  end
  fclose(fid);
end
