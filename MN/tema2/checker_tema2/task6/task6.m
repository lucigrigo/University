function task6()
  clc
  clear
  close all
  format long
  pkg load image
  mkdir('out/');
  
  database_path = './dataset';
  in_path = strcat(pwd, '/in');
  max_dif = 10*200^3;

  [m, A, eigenfaces pr_img] = eigenface_core(database_path);

  fid = fopen('./out/task6.txt', 'w');
   
  for i = 1 : 6
    image_path = strcat(in_path,'/',int2str(i),'.jpg');
    
    [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img);
    
    if (min_dist < max_dif)
        output_name = strcat(int2str(output_img_index),'.jpg');
        selected_image = strcat(database_path,'/',output_name);
        selected_image = imread(selected_image);
        
        test_image = imread(image_path);

        % figure,imshow(test_image)
        % title('Test Image');
        % figure,imshow(selected_image);
        % title('Equivalent Image');
        
        msg = strcat('Matched image is: ',output_name);
        % disp(msg);
        fprintf(fid, "%s\n", msg);
    elseif (min_dist < max_dif * 5 / 4)
        % printf(strcat('This image is a human face, but not a known one', '\n'));
        fprintf(fid, "This image is a human face, but not a known one\n");
    else
        % printf(strcat('This image is not a human face', '\n'));
        fprintf(fid, "This image is not a human face\n");
    end
  end
  fclose(fid);
end