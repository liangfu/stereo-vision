package com.android.sv;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;

public class OpenCVView extends OpenCVViewBase {
    private static final String TAG = "Sample::View";

    public OpenCVView(Context context) {
        super(context);
    }

    @Override
    protected Bitmap processFrame(byte[] data) {
        int frameSize = getFrameWidth() * getFrameHeight();
        int[] rgba = new int[frameSize];
		
		// for (int i = 0; i < frameSize; i++){
		// 	rgba[i] = data[i];
		// }
        FindFeatures(getFrameWidth(), getFrameHeight(), data, rgba);

        Bitmap bmp = Bitmap.createBitmap(getFrameWidth(), getFrameHeight(), 
										 Bitmap.Config.ARGB_8888);
        bmp.setPixels(rgba, 0/* offset */, getFrameWidth() /* stride */, 
					  0, 0, getFrameWidth(), getFrameHeight());
        return bmp;
    }

	// public native boolean setSourceImage(int[] pixels, 
	// 									 int width, int height);
	// public native byte[] getSourceImage();
	// public native void extractSURFFeature();
    public native void FindFeatures(int width, int height, 
									byte yuv[], int[] rgba);

    static {
        Log.i(TAG, "loadLibrary - ready");
		try{
			System.loadLibrary("tvr_jni");
		}catch(UnsatisfiedLinkError e){
			System.err.println("Native code library failed to load.\n" + e);
		}
        Log.i(TAG, "loadLibrary - finish");
    }
}



// public class OpenCVView extends OpenCVViewBase {
// 	static{
// 		System.loadLibrary("opencv");
// 	}
// 	public native boolean setSourceImage(int[] pixels, int width, int height);
// 	public native byte[] getSourceImage();
// 	public native void extractSURFFeature();
// }
