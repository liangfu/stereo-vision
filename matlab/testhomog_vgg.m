% TESTHOMOG Usage:
%   H = testhomog_vgg(imgfile1, imgfile2)

% Demonstration of feature matching via simple correlation, and then using
% RANSAC to estimate the homography matrix and at the same time identify
% (mostly) inlying matches

% Peter Kovesi  
% School of Computer Science & Software Engineering
% The University of Western Australia
% pk at csse uwa edu au
% http://www.csse.uwa.edu.au/~pk
%
% February 2004

% Adapted to use vgg functions by Peter Kovesi and Andrew Zisserman

function [H, F, finalmatches, initmatches] = testhomog_vgg(imgfile1, imgfile2)

    close all    
    
    thresh = 500;   % Harris corner threshold
    nonmaxrad = 3;  % Non-maximal suppression radius
    dmax = 100;
    w = 11;    % Window size for correlation matching

    % gray images as input
    im1 = imgfile1;%imread(imgfile1); % rgb2gray(imread('im1.png'));
    im2 = imgfile2;%imread(imgfile2); % rgb2gray(imread('im2.png'));

    % Find Harris corners in image1 and image2
    [cim1, r1, c1] = harris(im1, 1, thresh, 3);
    show(im1,1), hold on, plot(c1,r1,'r+');

    [cim2, r2, c2] = harris(im2, 1, thresh, 3);
    show(im2,2), hold on, plot(c2,r2,'r+');

    drawnow

tic
    [m1,m2] = matchbycorrelation(im1, [r1';c1'], im2, [r2';c2'], w, dmax);
toc
% Display putative matches

    show(im1,3), set(3,'name','Putative matches'), hold on    
    initmatches = [];
    for n = 1:length(m1);
        line([m1(2,n) m2(2,n)], [m1(1,n) m2(1,n)])
        initmatch = [[m1(2,n) m1(1,n)], [m2(2,n) m2(1,n)]];
        initmatches = [initmatches; initmatch];
    end

    % Assemble homogeneous feature coordinates for fitting of the
    % homography matrix, note that [x,y] corresponds to [col, row]
    x1 = [m1(2,:); m1(1,:); ones(1,length(m1))];
    x2 = [m2(2,:); m2(1,:); ones(1,length(m1))];    
    
    t = .001;  % Distance threshold for deciding outliers
%    [H, inliers] = ransacfithomography_vgg(x1, x2, t);
    t = .008;[H, inliers] = ransacfithomography(x1, x2, t);

tic
    finalmatches = [];finalmatches_h = [];
    for n = inliers
        finalmatch = [[m1(2,n) m1(1,n)], [m2(2,n) m2(1,n)]];
        finalmatches = [finalmatches;finalmatch];
        finalmatch_h = [m1(2,n) m1(1,n), 1, m2(2,n) m2(1,n), 1];
        finalmatches_h = [finalmatches_h;finalmatch_h];
    end
    fm_h_1 = finalmatches_h(:,1:3)
    fm_h_2 = finalmatches_h(:,4:6)
    fm_h_1 = fm_h_1'
    fm_h_2 = fm_h_2'

    [F, e1, e2] = affinefundmatrix(fm_h_1, fm_h_2)
% $$$     [F, e1, e2] = affinefundmatrix(finalmatches(1:2,:), finalmatches(3:4,:))
% $$$     [F, inliers2] = ransacfitfundmatrix(x1, x2, t);
toc
    fprintf('Number of inliers was %d (%d%%) \n', ...
	    length(inliers),round(100*length(inliers)/length(m1)))
    fprintf('Number of putative matches was %d \n', length(m1))        
    
    % Display both images overlayed with inlying matched feature points
    show(double(im1)+double(im2),4), set(4,'name','Inlying matches'), hold on 
    plot(m1(2,inliers),m1(1,inliers),'r+');
    plot(m2(2,inliers),m2(1,inliers),'g+');    

    % Step through each matched pair of points and display the
    % line linking the points on the overlayed images.

    for n = inliers
        line([m1(2,n) m2(2,n)], [m1(1,n) m2(1,n)],'color',[0 0 1]);
    end

    return
    
    
