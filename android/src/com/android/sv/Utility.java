package com.android.tvr;

import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.text.format.DateFormat;

public class Utility {
	public static String createName(long dateTaken) {
		return DateFormat.format("yyyyMMddkkmmss", dateTaken).toString();
	}

	public static Bitmap rotate(Bitmap b, int degrees) {
		if (degrees != 0 && b != null) {
			Matrix m = new Matrix();
			m.setRotate(degrees, (float) b.getWidth() / 2,
					(float) b.getHeight() / 2);
			try {
				Bitmap b2 = Bitmap.createBitmap(b, 0, 0, b.getWidth(),
						b.getHeight(), m, true);
				if (b != b2) {
					b.recycle();
					b = b2;
				}
			} catch (OutOfMemoryError ex) {
				// We have no memory to rotate. Return the original bitmap.
			}
		}
		return b;
	}

	public static int getRotationFromImage(String imagePath) {
		int degrees = 0;
		try {
			ExifInterface exif = new ExifInterface(imagePath);
			int orientation = exif.getAttributeInt(
					ExifInterface.TAG_ORIENTATION, 0);
			switch (orientation) {
			case ExifInterface.ORIENTATION_ROTATE_90:
				degrees = 90;
				break;
			case ExifInterface.ORIENTATION_ROTATE_180:
				degrees = 180;
				break;
			case ExifInterface.ORIENTATION_ROTATE_270:
				degrees = 270;
				break;
			default:
				degrees = 0;
				break;
			}

		} catch (Exception e) {

		}
		return degrees;
	}
}