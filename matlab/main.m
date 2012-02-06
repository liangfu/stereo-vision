
im1 = imread('../data/test_r.jpg');im1 = rgb2gray(im1);
im2 = imread('../data/test_l.jpg');im2 = rgb2gray(im2);
dispMap = stereomatch(im1, im2, 9, 16, 0);imshow(dispMap, [0 16]);
