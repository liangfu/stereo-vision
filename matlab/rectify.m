function [H12,H21,F12] = rectify

% Fundamental matrices

% I obtained these by running ./sift-match on SIFT keypoints from the
% image pairs.

% Transfer between image 1 and 2, i.e. x1' * F12 * x2 = 0

    F12 =  [ 4.2513858033999e-07 -4.0431226807414e-05   0.0077414843253791
             -1.1731941413018e-05   3.842141268251e-06    -0.11110986024141
             0.0012875135289505      0.1209783628583                    1 ];

    X = [ 305.609 26.6088 246.421 54.3379
          492.702 276.988 544.887 287.694
          522.785 80.4814 462.385 115.812
          364.584 279.086 424.696 295.6
          331.308 254.035 384.666 273.697
          355.993 260.265 411.168 278.89
          418.566 200.337 467.549 222.592
          216.461 15.9762 138.71 36.9085
          232.157 241.982 309.627 265.462
          316.861 56.3985 256.17 84.615
          258.518 23.244 191.844 47.6098
          521.023 54.8749 461.206 93.5966
          141.054 7.54285 40.1972 20.9542
          491.102 33.0556 434.33 72.7077
          323.366 20.4939 264.22 50.0497
          338.525 22.0519 280.848 52.8956
          540.868 80.653 478.55 117.031
          512.72 31.5519 454.035 72.6285
          315.623 15.4164 256.567 44.8631
          315.623 15.4164 256.567 44.8631
          527.796 90.5441 465.978 124.812
          381.222 17.807 326.104 51.5909
          231.16 225.313 309.509 249.217
          523.185 65.1528 462.719 102.58
          255.546 99.2282 187.106 123.635
          304.377 44.796 243.152 72.2766
          352.213 28.0097 295.031 59.432
          378.962 155.807 423.055 182.816
          454.003 46.1736 398.622 82.4458
          252.478 30.1319 182.677 54.2988
          128.006 240.785 227.185 267.356
          219.915 198.573 298.802 223.686
          83.1585 309.322 192.358 339.36
          86.6391 313.111 194.85 342.818
          401.264 20.2752 347.456 55.6018
          550.996 91.8475 486.969 126.924
          354.473 34.1824 297.942 65.5933
          465.426 253.042 518.831 268.167
          405.495 182.739 452.177 207.237
          539.715 323.96 595.509 325.532
          513.775 97.9685 454.156 131.215
          214.021 47.5983 135.454 68.8427
          105.265 323.196 210.089 351.77
          217.696 45.3997 139.969 66.6746
          539.795 65.7604 477.426 103.815
          539.795 65.7604 477.426 103.815
          313.24 37.3028 252.296 65.6123
          408.165 196.597 457.594 219.633
          96.793 278.284 203.128 306.483
          565.263 95.2286 498.908 130.389
          534.386 88.4716 472.15 123.519
          248.698 33.5376 178.266 57.3788
          546.378 63.8086 483.439 102.294
          99.9456 275.605 205.896 303.125
          528.947 322.687 587.457 324.836
          365.669 229.69 418.364 250.462
          315.676 41.0734 255.016 69.3287
          525.648 84.6874 464.251 120.047
          561.866 79.2706 496.592 116.146
          559.567 84.1837 494.463 120.448
          86.1349 281.982 194.605 310.512
          217.171 8.25271 141.518 28.9524
          542.595 62.5089 480.169 101.01
          542.595 62.5089 480.169 101.01
          533.577 70.1914 471.842 107.409
          268.724 19.2495 202.812 44.6171
          409.926 204.982 459.878 227.273
          367.762 31.6961 312.479 63.9908
          434.206 225.685 486.083 245.14
          534.008 79.8828 471.631 115.982
          454.38 210.02 503.421 230.846
          370.341 71.5554 314.195 101.627
          370.341 71.5554 314.195 101.627
          456.63 198.643 504.309 220.912
          358.335 22.3839 301.422 54.4783
          395.654 180.724 443.027 205.646
          562.406 82.5006 496.957 119.351
          562.406 82.5006 496.957 119.351
          247.096 36.654 176.197 60.1211
          418.921 223.742 471.03 244.002
          412.113 194.205 460.831 217.514
          118.698 243.274 219.3 269.984
          325.891 78.3883 265.879 106.117
          355.945 17.4176 299.339 49.7236
          97.9262 261.134 203.967 288.574
          97.9262 261.134 203.967 288.574
          268.74 22.1997 202.446 47.5369
          336.341 77.0648 277.622 105.07
          322.577 13.3984 264.034 43.4137
          275.623 14.4103 210.89 40.4827
          249.362 39.0811 178.616 62.7643
          348.294 23.4954 290.975 54.8945
          556.931 51.3906 493.502 92.4845 ];

    % Matching 2D points hard coded
    [x1,x2] = correspondences_F12(X);

    % Get images

    fprintf( 1, 'Getting images...\n' );
    %myflush();
    Img1 = imread( 'test_left.pgm' );
    Img2 = imread( 'test_right.pgm' );

    % Get image size

    [rows,cols,depth] = size(Img1);

    % Get homographies.

    [H12,H21,bSwap] = rectify_homographies( F12, x1, x2, rows, cols );

    % Transform the images

    fprintf( 1, 'Rectifying...\n' );
    %myflush();
    Img1_new = rectify_transform( Img1, H12 );
    Img2_new = rectify_transform( Img2, H21 );

    % Chop off excess rows

    [Img1_new,Img2_new] = chop_rows( Img1_new, Img2_new, H12, H21, rows, cols );

    fprintf( 1, 'Writing images to disk...\n' );
    %myflush();

    %myimwrite( 'desk1_rect.png', Img1_new );
    %myimwrite( 'desk2_rect.png', Img2_new );
    imwrite( Img1_new, 'desk1_rect.png' );
    imwrite( Img2_new, 'desk2_rect.png' );

%-----------------------------------------------------------------------------

function [Img1,Img2] = chop_rows( Img1, Img2, H12, H21, rows, cols );
    box1 = transform_bbox( H12, rows, cols );
    box2 = transform_bbox( H21, rows, cols );
    min1 = min( box1(2,:) );
    min2 = min( box2(2,:) );
    if min1 < min2
        Img1 = Img1(min2-min1+1:end,:,:);
    else
        Img2 = Img2(min1-min2+1:end,:,:);
    end;
    max1 = max( box1(2,:) );
    max2 = max( box2(2,:) );
    if max1 > max2
        Img1 = Img1(1:size(Img1,1)-(max1-max2),:,:);
    else
        Img2 = Img2(1:size(Img2,1)-(max2-max1),:,:);
    end;

%-----------------------------------------------------------------------------

function box = transform_bbox( H, rows, cols )

    box = [ 1 cols 1 cols ; 1 1 rows rows ; 1 1 1 1 ];
    box = H * box;
    box = round( box(1:2,:) ./ repmat( box(3,:), 2, 1 ));

%-----------------------------------------------------------------------------

function Img_new = rectify_transform( Img, H )

% Peter's image transform wants a specific max width/height for the
% image, but we want the natural width/height, so we have to calculate it.

    rows = size( Img, 1 );
    cols = size( Img, 2 );
    xnew = transform_bbox( H, rows, cols );

    sze = max( xnew' )' - min( xnew' )' + [ 1 ; 1 ];

    Img_new = imTrans( Img, H, [], max( sze ));

%-----------------------------------------------------------------------------

function [H1,H2,bSwap] = rectify_homographies( F, x1, x2, rows, cols )

% F: a fundamental matrix

% x1 and x2: corresponding points such that x1_i' * F * x2_i = 0

% Initialize

    H1 = [];
    H2 = [];
    bSwap = 0;

    % Center of image

    cy = round( rows/2 );
    cx = round( cols/2 );

    % Fix F to be rank 2 to numerical accuracy

    [U,D,V] = svd( F );
    D(3,3) = 0;
    F = U*D*V';

    % Get epipole.  e12 is the epipole in image 1 for camera 2.

    e12 = null( F' );             % Epipole in image 1 for camera 2
    e21 = null( F );              % Epipole in image 2 for camera 1

    % Put epipoles in front of camera

    if e12 < 0, e12 = -e12; end;
    if e21 < 0, e21 = -e21; end;

    % Make sure the epipoles are inside the images

    check_epipoles_in_image( e12, e21, rows, cols );

    % Check that image 1 is to the left of image 2

    if e12(1)/e12(3) < cx
        fprintf( 1, 'Swapping left and right images...\n' );
        %myflush();
        tmp = e12;
        e12 = e21;
        e21 = tmp;
        F = F';
        bSwap = 1;
    end;

    % Now we have
    % F' * e12 = 0, 
    % F  * e21 = 0,

    % Let's get the rectifying homography Hprime for image 1 first

    Hprime = map_to_infinity( e12, cx, cy );
    e12_new = Hprime * e12;
    % Normalize Hprime so that Hprime*eprime = (1,0,0)'
    Hprime = Hprime / e12_new(1);
    e12_new = Hprime * e12;
    fprintf( 1, 'Epipole 1/2 mapped to infinity: (%g, %g, %g)\n', e12_new );

    % Get canonical camera matrices for F12 and compute H0, one possible
    % rectification homography for image 2

    [P,Pprime] = get_canonical_cameras( F );
    M = Pprime(:,1:3);
    H0 = Hprime * M;

    % Test that F12 is a valid F for P,Pprime

    test_p_f( P, Pprime, F );

    % Now we need to find H so that the epipolar lines match
    % each other, i.e., inv(H)' * l = inv(Hprime)' * lprime
    % and the disparity is minimized, i.e.,
    % min \sum_i d(H x_i, Hprime xprime_i)^2

    % Transform data initially according to Hprime (img 1) and H0 (img 2)

    x1hat = Hprime * x1;
    x1hat = x1hat ./ repmat( x1hat(3,:), 3, 1 );
    x2hat = H0 * x2;
    x2hat = x2hat ./ repmat( x2hat(3,:), 3, 1 );
    rmse_x = sqrt( mean( (x1hat(1,:) - x2hat(1,:) ).^2 ));
    rmse_y = sqrt( mean( (x1hat(2,:) - x2hat(2,:) ).^2 ));
    fprintf( 1, 'Before Ha, RMSE for corresponding points in Y: %g X: %g\n', ...
             rmse_y, rmse_x );

    % Estimate [ a b c ; 0 1 0 ; 0 0 1 ] aligning H, Hprime

    n = size(x1,2);
    A = [ x2hat(1,:)', x2hat(2,:)', ones(n,1) ];
    b = x1hat(1,:)';
    abc = A\b;
    HA = [ abc' ; 0 1 0 ; 0 0 1 ];
    H = HA*H0;
    x2hat = H * x2;
    x2hat = x2hat ./ repmat( x2hat(3,:), 3, 1 );
    rmse_x = sqrt( mean(( x1hat(1,:) - x2hat(1,:) ).^2 ));
    rmse_y = sqrt( mean(( x1hat(2,:) - x2hat(2,:) ).^2 ));
    fprintf( 1, 'After Ha, RMSE for corresponding points in Y: %g X: %g\n', ...
             rmse_y, rmse_x );

    % Return the homographies as appropriate

    if bSwap
        H1 = H;
        H2 = Hprime;
    else
        H1 = Hprime;
        H2 = H;
    end;

%-----------------------------------------------------------------------------

function check_epipoles_in_image( e1, e2, rows, cols )

% Check whether given epipoles are in the image or not

    if abs( e1(3) ) < 1e-6 & abs( e2(3) ) < 1e-6, return; end;

    e1 = e1 / e1(3);
    e2 = e2 / e2(3);
    if ( e1(1) <= cols & e1(1) >= 1 & e1(2) <= rows & e1(2) >= 1 ) | ...
                  ( e2(1) <= cols & e2(1) >= 1 & e2(2) <= rows & e2(2) >= 1 )
        err_msg = sprintf( 'epipole (%g,%g) or (%g,%g) is inside image', ...
                           e1(1:2), e2(1:2) );
        error( [ err_msg, ' -- homography does not work in this case!' ] );
    end;

%-----------------------------------------------------------------------------

function [P,Pprime] = get_canonical_cameras( F )

% Get the "canonical" cameras for given fundamental matrix
% according to Hartley and Zisserman (2004), p256, Result 9.14

% But ensure that the left 3x3 submatrix of Pprime is nonsingular
% using Result 9.15, that the general form is
% [ skewsym( e12 ) * F + e12 * v', k * e12 ] where v is an arbitrary
% 3-vector and k is an arbitrary scalar

    P = [ 1 0 0 0
          0 1 0 0
          0 0 1 0 ];

    e12 = null( F' );
    M = skewsym( e12 ) * F + e12 * [1 1 1];
    Pprime = [ M, e12 ];

%-----------------------------------------------------------------------------

function test_p_f( P, Pprime, F )

% Test that camera matrices Pprime and P are consistent with
% fundamental matrix F
% Meaning  (Pprime*X)' * F * (P*X) = 0,  for all X in 3space

% Get the epipole in camera 1 for camera 2

    C2 = null( P );
    eprime = Pprime * C2;

    % Construct F from Pprime, P, and eprime

    Fhat = skewsym( eprime ) * Pprime * pinv( P );

    % Check that it's close to F

    alpha = Fhat(:)\F(:);
    if norm( alpha*Fhat-F ) > 1e-10
        fprintf( 1, 'Warning: supplied camera matrices are inconsistent with F\n' );
    else
        fprintf( 1, 'Supplied camera matrices OK\n' );
    end;

%-----------------------------------------------------------------------------

function H = map_to_infinity( x, cx, cy )

% Given a point and the desired origin (point of minimum projective
% distortion), compute a homograph H = G*R*T taking the point to the
% origin, rotating it to align with the X axis, then mapping it to
% infinity.

% First map cx,cy to the origin

    T = [ 1 0 -cx
          0 1 -cy
          0 0 1 ];
    x = T * x;

    % Now rotate the translated x to align with the X axis.

    cur_angle = atan2( x(2), x(1) );
    R = [ cos( -cur_angle ), -sin( -cur_angle ), 0
          sin( -cur_angle ),  cos( -cur_angle ), 0
          0,                  0, 1 ];
    x = R * x;

    % Now the transformation G mapping x to infinity

    if abs( x(3)/norm(x) ) < 1e-6
        % It's already at infinity
        G = eye(3)
    else
        f = x(1)/x(3);
        G = [    1   0  0
                 0   1  0
                 -1/f  0  1 ];
    end;

    H = G*R*T;

%-----------------------------------------------------------------------------

function s = skewsym( x )
    s = [   0   -x(3)  x(2)
            x(3)   0   -x(1)
            -x(2)  x(1)   0   ];

%-----------------------------------------------------------------------------

function [x1,x2] = correspondences_F12(X)

% The data are desk2.png (x,y) desk1.png (x,y)

    x1 = X(:,3:4)';
    x2 = X(:,1:2)';
    n = size( x1, 2 );
    x1 = [ x1 ; ones(1,n) ];
    x2 = [ x2 ; ones(1,n) ];
    n = size(x1,2);

%-----------------------------------------------------------------------------

