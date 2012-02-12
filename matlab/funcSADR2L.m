% *************************************************************************
% Title: Function-Compute Correlation between two images using the 
% similarity measure of Sum of Absolute Differences (SAD) with
% Right Image 
% as reference.
% Author: Siddhant Ahuja
% Created: May 2008
% Copyright Siddhant Ahuja, 2008
% Inputs: Left Image (var: leftImage), Right Image (var:
% rightImage),
% Window Size (var: windowSize), Minimum Disparity (dispMin),
% Maximum
% Disparity (dispMax)
% Outputs: Disparity Map (var: dispMap), Time taken (var:
% timeTaken)
% Example Usage of Function: [dispMap,
% timeTaken]=funcSADR2L('StereogramLeft.jpg',
% 'StereogramRight.jpg', 9, 0, 16);
% *************************************************************************
function [dispMap, timeTaken]=funcSADR2L(leftImage, rightImage, ...
                                         windowSize, dispMin, ...
                                         dispMax)
try 
    % Grab the image information (metadata) of left image using the
    % function imfinfo
    leftImageInfo=imfinfo(leftImage);
    % Since SADR2L is applied on a grayscale image, determine if
    % the
    % input left image is already in grayscale or color
    if(getfield(leftImageInfo,'ColorType')=='truecolor')
        % Read an image using imread function, convert from RGB
        % color space to
        % grayscale using rgb2gray function and assign it to
        % variable leftImage
        leftImage=rgb2gray(imread(leftImage));
        % Convert the image from uint8 to double
        leftImage=double(leftImage);
    else if(getfield(leftImageInfo,'ColorType')=='grayscale')
            % If the image is already in grayscale, then just read
            % it.        
            leftImage=imread(leftImage);
            % Convert the image from uint8 to double
            leftImage=double(leftImage);
        else
            error(['The Color Type of Left Image is not acceptable. ' ...
                   'Acceptable color types are truecolor or ' ...
                   'grayscale.']);
        end
    end
catch
    % if it is not an image but a variable
    leftImage=leftImage;
end
try
    % Grab the image information (metadata) of right image using
    % the function imfinfo
    rightImageInfo=imfinfo(rightImage);
    % Since SADR2L is applied on a grayscale image, determine if
    % the
    % input right image is already in grayscale or color
    if(getfield(rightImageInfo,'ColorType')=='truecolor')
        % Read an image using imread function, convert from RGB
        % color space to
        % grayscale using rgb2gray function and assign it to
        % variable rightImage
        rightImage=rgb2gray(imread(rightImage));
        % Convert the image from uint8 to double
        rightImage=double(rightImage);
    else if(getfield(rightImageInfo,'ColorType')=='grayscale')
            % If the image is already in grayscale, then just read
            % it.        
            rightImage=imread(rightImage);
            % Convert the image from uint8 to double
            rightImage=double(rightImage);
        else
            error(['The Color Type of Right Image is not acceptable. ' ...
                   'Acceptable color types are truecolor or ' ...
                   'grayscale.']);
        end
    end
catch
    % if it is not an image but a variable
    rightImage=rightImage;
end
% Find the size (columns and rows) of the left image and assign the
% rows to
% variable nrLeft, and columns to variable ncLeft
[nrLeft,ncLeft] = size(leftImage);
% Find the size (columns and rows) of the right image and assign
% the rows to
% variable nrRight, and columns to variable ncRight
[nrRight,ncRight] = size(rightImage);
% Check to see if both the left and right images have same number
% of rows
% and columns
if(nrLeft==nrRight && ncLeft==ncRight)
else
    error(['Both left and right images should have the same number ' ...
           'of rows and columns');
end
% Check the size of window to see if it is an odd number.
if (mod(windowSize,2)==0)
    error('The window size must be an odd number.');
end
% Check whether minimum disparity is less than the maximum
% disparity.
if (dispMin>dispMax)
    error(['Minimum Disparity must be less than the Maximum ' ...
           'disparity.']);
end
% Create an image of size nrLeft and ncLeft, fill it with zeros and
% assign
% it to variable dispMap
dispMap=zeros(nrLeft, ncLeft);
% Find out how many rows and columns are to the left/right/up/down
% of the
% central pixel based on the window size
win=(windowSize-1)/2;
tic; % Initialize the timer to calculate the time consumed.
for(i=1+win:1:nrLeft-win)
    for(j=1+win:1:ncLeft-win-dispMax)
        prevSAD = 65532;
        temp=0.0;
        bestMatchSoFar = dispMin;
        for(dispRange=dispMin:1:dispMax)
            sad=0.0;
            for(a=-win:1:win)
                for(b=-win:1:win)
                    if (j+b+dispRange <= ncLeft)
                        temp=rightImage(i+a,j+b)-leftImage(i+a,j+b+ ...
                                                           dispRange);
                        if(temp<0.0)
                            temp=temp*-1.0;
                        end
                        sad=sad+temp;
                    end
                end
            end
            if (prevSAD > sad)
                prevSAD = sad;
                bestMatchSoFar = dispRange;
            end
        end
        dispMap(i,j) = bestMatchSoFar;
    end
end
% Stop the timer to calculate the time consumed.
timeTaken=toc;