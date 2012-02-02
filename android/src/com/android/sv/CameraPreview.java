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
// package com.example.android.apis.graphics;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.hardware.Camera;
import android.hardware.Camera.CameraInfo;
import android.hardware.Camera.Size;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
// import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;

import java.io.IOException;
import java.util.List;

// Need the following import to get access to the app resources, since this
// class is in a sub-package.
// import com.example.android.apis.R;
// import com.android.tvr.R;

// ----------------------------------------------------------------------

public class CameraPreview extends Activity {
    private Preview mPreview;
    Camera mCamera;
    int numberOfCameras;
    int cameraCurrentlyLocked;

    // The first rear facing camera
    int defaultCameraId;

    @Override
		protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Hide the window title.
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

        // Create a RelativeLayout container that will hold a SurfaceView,
        // and set it as the content of our activity.
        mPreview = new Preview(this);
        setContentView(mPreview);

        // Find the total number of cameras available
        numberOfCameras = Camera.getNumberOfCameras();

        // Find the ID of the default camera
        CameraInfo cameraInfo = new CameraInfo();
		for (int i = 0; i < numberOfCameras; i++) {
			Camera.getCameraInfo(i, cameraInfo);
			if (cameraInfo.facing == CameraInfo.CAMERA_FACING_BACK) {
				defaultCameraId = i;
			}
		}
    }

    @Override
		protected void onResume() {
        super.onResume();

        // Open the default i.e. the first rear facing camera.
        mCamera = Camera.open();
        cameraCurrentlyLocked = defaultCameraId;
        mPreview.setCamera(mCamera);
    }

    @Override
		protected void onPause() {
        super.onPause();

        // Because the Camera object is a shared resource, it's very
        // important to release it when the activity is paused.
        if (mCamera != null) {
            mPreview.setCamera(null);
            mCamera.release();
            mCamera = null;
        }
    }

    @Override
		public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate our menu which can gather user input for switching camera
        // MenuInflater inflater = getMenuInflater();
        // inflater.inflate(R.menu.camera_menu, menu);
        return true;
    }

    @Override
		public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
			// case R.id.switch_cam:
			//     // check for availability of multiple cameras
			//     if (numberOfCameras == 1) {
			//         AlertDialog.Builder builder = new AlertDialog.Builder(this);
			//         builder.setMessage(this.getString(R.string.camera_alert))
			//                .setNeutralButton("Close", null);
			//         AlertDialog alert = builder.create();
			//         alert.show();
			//         return true;
			//     }

			//     // OK, we have multiple cameras.
			//     // Release this camera -> cameraCurrentlyLocked
			//     if (mCamera != null) {
			//         mCamera.stopPreview();
			//         mPreview.setCamera(null);
			//         mCamera.release();
			//         mCamera = null;
			//     }

			//     // Acquire the next camera and request Preview to reconfigure
			//     // parameters.
			//     mCamera = Camera
			//             .open((cameraCurrentlyLocked + 1) % numberOfCameras);
			//     cameraCurrentlyLocked = (cameraCurrentlyLocked + 1)
			//             % numberOfCameras;
			//     mPreview.switchCamera(mCamera);

			//     // Start the preview
			//     mCamera.startPreview();
			//     return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }
}

// ----------------------------------------------------------------------

