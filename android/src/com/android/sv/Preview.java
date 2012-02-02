/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.sv;

import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.PixelFormat;
import android.hardware.Camera.Size;
import android.hardware.Camera;
import android.content.Context;
import android.hardware.Camera.PreviewCallback;

import java.io.IOException;
import java.util.List;
import java.lang.reflect.Method;


/**
 * A simple wrapper around a Camera and a SurfaceView that renders a centered preview of the Camera
 * to the surface. We need to center the SurfaceView because not all devices have cameras that
 * support preview sizes at the same aspect ratio as the device's display.
 */
class Preview extends ViewGroup implements SurfaceHolder.Callback {
    private final String TAG = "Preview";

    SurfaceView mSurfaceView;
    SurfaceHolder mHolder;
    Size mPreviewSize;
    List<Size> mSupportedPreviewSizes;
    Camera mCamera;

    Preview(Context context) {
        super(context);

        mSurfaceView = new SurfaceView(context);
        addView(mSurfaceView);

        // Install a SurfaceHolder.Callback so we get notified when the
        // underlying surface is created and destroyed.
        mHolder = mSurfaceView.getHolder();
        mHolder.addCallback(this);
        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    public void setCamera(Camera camera) {
        mCamera = camera;
        if (mCamera != null) {
            mSupportedPreviewSizes = 
				mCamera.getParameters().getSupportedPreviewSizes();
            requestLayout();
        }
    }

    public void switchCamera(Camera camera) {
		setCamera(camera);
		try {
			camera.setPreviewDisplay(mHolder);
		} catch (IOException exception) {
			Log.e(TAG, "IOException caused by setPreviewDisplay()", 
				  exception);
		}
		Camera.Parameters parameters = camera.getParameters();
		parameters.setPreviewSize(mPreviewSize.width, mPreviewSize.height);
		requestLayout();

		camera.setParameters(parameters);
    }

    @Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        // We purposely disregard child measurements because act as a
        // wrapper to a SurfaceView that centers the camera preview instead
        // of stretching it.
        final int width = resolveSize(getSuggestedMinimumWidth(), 
									  widthMeasureSpec);
        final int height = resolveSize(getSuggestedMinimumHeight(), 
									   heightMeasureSpec);
        setMeasuredDimension(width, height);

        if (mSupportedPreviewSizes != null) {
            mPreviewSize = getOptimalPreviewSize(mSupportedPreviewSizes, 
												 width, height);
        }
    }

    @Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {
        if (changed && getChildCount() > 0) {
            final View child = getChildAt(0);

            final int width = r - l;
            final int height = b - t;

            int previewWidth = width;
            int previewHeight = height;
            if (mPreviewSize != null) {
                previewWidth = mPreviewSize.width;
                previewHeight = mPreviewSize.height;
            }

            // Center the child SurfaceView within the parent.
            // if (width * previewHeight > height * previewWidth) {
            //     final int scaledChildWidth = 
			// 		previewWidth * height / previewHeight;
            //     child.layout((width - scaledChildWidth) / 2, 0,
			// 				 (width + scaledChildWidth) / 2, height);
            // } else
			{
                final int scaledChildHeight = height;
					// previewHeight * width / previewWidth;
                child.layout(0, (height - scaledChildHeight) / 2,
							 width, (height + scaledChildHeight) / 2);
            }
        }
    }

    public void surfaceCreated(SurfaceHolder holder) {
        // The Surface has been created, acquire the camera and tell it where
        // to draw.
        try {
            if (mCamera != null) {
				// setDisplayOrientation(mCamera, 90);
				mCamera.setDisplayOrientation(90);
                mCamera.setPreviewDisplay(holder);
				mCamera.startPreview();
            }
        } catch (IOException exception) {
            Log.e(TAG, "IOException caused by setPreviewDisplay()", 
				  exception);
        }

		// mCamera.setPreviewCallback(new PreviewCallback() {
		// 		public void onPreviewFrame(byte[] data, 
		// 								   Camera camera) {
		// 			synchronized (Preview.this) {
		// 				// mFrame = data;
		// 				Preview.this.notify();
		// 			}
		// 			// Preview.this.notify();
		// 		}
		// 	});
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        // Surface will be destroyed when we return, so stop the preview.
        if (mCamera != null) {
            mCamera.stopPreview();
            mCamera.release();
			mCamera = null;
        }
    }


    private Size getOptimalPreviewSize(List<Size> sizes, int w, int h) 
	{
        final double ASPECT_TOLERANCE = 0.1;
        double targetRatio = (double) w / h;
        if (sizes == null) return null;

        Size optimalSize = null;
        double minDiff = Double.MAX_VALUE;

        int targetHeight = h;

        // Try to find an size match aspect ratio and size
        for (Size size : sizes) {
            double ratio = (double) size.width / size.height;
            if (Math.abs(ratio - targetRatio) > ASPECT_TOLERANCE) continue;
            if (Math.abs(size.height - targetHeight) < minDiff) {
                optimalSize = size;
                minDiff = Math.abs(size.height - targetHeight);
            }
        }

		// for (Size size : sizes) {
		// 	if (size.width<=w && size.height<=h) {
		// 		if (optimalSize==null) {
		// 			optimalSize=size;
		// 		}
		// 		else {
		// 			int resultArea=optimalSize.width*optimalSize.height;
		// 			int newArea=size.width*size.height;
		// 			if (newArea>resultArea) {
		// 				optimalSize=size;
		// 			}
		// 		}
		// 	}
		// }

        // Cannot find the one match the aspect ratio, ignore the requirement
        if (optimalSize == null) {
            minDiff = Double.MAX_VALUE;
            for (Size size : sizes) {
                if (Math.abs(size.height - targetHeight) < minDiff) {
                    optimalSize = size;
                    minDiff = Math.abs(size.height - targetHeight);
                }
            }
        }

        return optimalSize;
    }

    public void surfaceChanged(SurfaceHolder holder, 
							   int format, int width, int height) 
	{
        // Now that the size is known, set up the camera parameters and begin
        // the preview.
        Camera.Parameters parameters = mCamera.getParameters();

        // parameters.setPreviewSize(mPreviewSize.width, mPreviewSize.height);
		Size size = getOptimalPreviewSize(parameters.
										  getSupportedPreviewSizes(), 
										  // width, height
										  height, width
										  );
        parameters.setPreviewSize(size.width, size.height);

		// parameters.setPictureFormat(PixelFormat.JPEG); 
		// parameters.set("orientation", "portrait");
		// parameters.setRotation(90);

        requestLayout();

        mCamera.setParameters(parameters);
        mCamera.startPreview();
    }
}
