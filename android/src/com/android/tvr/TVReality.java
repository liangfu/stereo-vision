package com.android.tvr;

import java.io.File;
import java.io.FileOutputStream;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.media.ExifInterface;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.provider.MediaStore.Images;
import android.provider.MediaStore.Images.Media;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.Toast;
import android.view.Window;

public class TVReality extends Activity {
	// private static final String IMAGE_DIRECTORY = "/sdcard/DCIM/Camera";
	// private static final int ACTIVITY_SELECT_CAMERA = 0;
	// private static final int ACTIVITY_SELECT_IMAGE = 1;
	private static final String TAG = "MAIN_ACTIVITY";
	// private static final int CAMERA_ID = Menu.FIRST;
	// private static final int GALLERY_ID = Menu.FIRST + 1;
	// private String mCurrentImagePath = null;
	// private OpenCV opencv = new OpenCV();
	// private ImageView mImageView;
    // private static final String TAG = "Sample::Activity";

    public TVReality() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

	@Override
	public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "onCreate");
		super.onCreate(savedInstanceState);
        // requestWindowFeature(Window.FEATURE_NO_TITLE);
		// mImageView = new ImageView(this);
		// setContentView(mImageView);
		setContentView(new OpenCVView(this));
        Log.i(TAG, "onCreate - finish");
	}

	// @Override
	// public boolean onCreateOptionsMenu(Menu menu) {
	// 	super.onCreateOptionsMenu(menu);
	// 	menu.add(0, CAMERA_ID, 0, "Camera");
	// 	menu.add(0, GALLERY_ID, 0, "Gallery");
	// 	return true;
	// }

	// @Override
	// public boolean onMenuItemSelected(int featureId, MenuItem item) {
	// 	switch (item.getItemId()) {
	// 	case CAMERA_ID:
	// 		Intent cameraIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
	// 		long timeTaken = System.currentTimeMillis();
	// 		mCurrentImagePath = IMAGE_DIRECTORY + "/"
	// 				+ Utility.createName(timeTaken) + ".jpg";
	// 		Log.i(TAG, mCurrentImagePath);
	// 		cameraIntent.putExtra(MediaStore.EXTRA_OUTPUT,
	// 				Uri.fromFile(new File(mCurrentImagePath)));
	// 		startActivityForResult(cameraIntent, ACTIVITY_SELECT_CAMERA);
	// 		return true;
	// 	case GALLERY_ID:
	// 		Intent galleryIntent = new Intent(Intent.ACTION_PICK,
	// 				Images.Media.INTERNAL_CONTENT_URI);
	// 		startActivityForResult(galleryIntent, ACTIVITY_SELECT_IMAGE);
	// 		return true;
	// 	}

	// 	return super.onMenuItemSelected(featureId, item);
	// }

	// @Override
	// protected void onActivityResult(int requestCode, int resultCode, Intent data) {
	// 	if (requestCode == ACTIVITY_SELECT_CAMERA
	// 			&& resultCode == Activity.RESULT_OK) {
	// 		ContentValues values = new ContentValues();
	// 		int degrees = Utility.getRotationFromImage(mCurrentImagePath);
	// 		try {
	// 			ExifInterface exif = new ExifInterface(mCurrentImagePath);
	// 			float[] position = new float[2];
	// 			if (exif.getLatLong(position)) {
	// 				values.put(Images.Media.LATITUDE, position[0]);
	// 				values.put(Images.Media.LONGITUDE, position[1]);
	// 			}
	// 		} catch (Exception e) {

	// 		}
	// 		// reduce the size of image
	// 		try {
	// 			BitmapFactory.Options option = new BitmapFactory.Options();
	// 			option.inSampleSize = 4;
	// 			Bitmap bitmap = BitmapFactory.decodeFile(mCurrentImagePath,
	// 					option);
	// 			if (degrees != 0) {
	// 				bitmap = Utility.rotate(bitmap, degrees);
	// 			}
	// 			FileOutputStream out = new FileOutputStream(mCurrentImagePath);
	// 			bitmap.compress(CompressFormat.JPEG, 100, out);
	// 		} catch (Exception e) {

	// 		}
	// 		values.put(Images.Media.MIME_TYPE, "image/jpeg");
	// 		values.put(Images.Media.DATA, mCurrentImagePath);
	// 		values.put(Images.Media.ORIENTATION, degrees);
	// 		getContentResolver().insert(Media.EXTERNAL_CONTENT_URI, values);
	// 	}
	// 	if (requestCode == ACTIVITY_SELECT_IMAGE && resultCode == RESULT_OK) {
	// 		try {
	// 			Uri currImageURI = data.getData();
	// 			String[] proj = { Images.Media.DATA, Images.Media.ORIENTATION };
	// 			Cursor cursor = managedQuery(currImageURI, proj, null, null,
	// 					null);
	// 			int columnIndex = cursor.getColumnIndex(proj[0]);
	// 			cursor.moveToFirst();
	// 			mCurrentImagePath = cursor.getString(columnIndex);
	// 			Bitmap bitmap = BitmapFactory.decodeFile(mCurrentImagePath);
	// 			Log.i(TAG, mCurrentImagePath);
	// 			int width = bitmap.getWidth();
	// 			int height = bitmap.getHeight();
	// 			int[] pixels = new int[width * height];
	// 			bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
	// 			opencv.setSourceImage(pixels, width, height);
	// 			long start = System.currentTimeMillis();
	// 			opencv.extractSURFFeature();
	// 			long end = System.currentTimeMillis();
	// 			byte[] imageData = opencv.getSourceImage();
	// 			long elapse = end - start;
	// 			Toast.makeText(this, "" + elapse + " ms is used to extract features.",
	// 					Toast.LENGTH_LONG).show();
	// 			bitmap = BitmapFactory.decodeByteArray(imageData, 0,
	// 					imageData.length);
	// 			mImageView.setImageBitmap(bitmap);
	// 		} catch (Exception e) {
	// 		}
	// 	}
	// }
}